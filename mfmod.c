#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include "rule.h"

/* The maximum size for the rule file */
#define PROCFS_MAX_SIZE 1024

/* Maxiumum number of rules */
#define MAX_NUM_RULES 128

/* The name for the rule file */
#define PROCFS_NAME "mfwrules"

static struct nf_hook_ops nfho;

/* The rule file */
static struct proc_dir_entry *rule_file;

/* The number of rules in the array */
static unsigned int num_rules = 0;

/* The array of rules */
static struct mfw_rule rules[MAX_NUM_RULES];

unsigned int hook_func(unsigned int hooknum,
	struct sk_buff *skb,
	const struct net_device *in,
	const struct net_device *out,
	int (*okfn)(struct sk_buff *))
{
    socket_buff = skb;

    if (!socket_buff) {
        return NF_ACCEPT;
    } else {
        ip_header = (stuct iphdr *)skb_network_header(socket_buff); // Network header

        // Drop all ICMP packets
        if (ip_header->protocol == IPPROTO_ICMP) {
            return NF_DROP;
        }
    }
}

/* A function to handle reads from the proc file */
int read_rule_file(char *buffer,
	char **buffer_location,
	off_t offset,
	int buffer_length,
	int *eof,
	void *data)
{
	int ret = 0;

	return ret;
}

/* A function to handle writes to the proc file */
int write_rule_file(struct file *file,
	const char *buffer,
	unsigned long count,
	void *data)
{

	struct mfw_rule rule;

	/* Make sure we have enough space for the new rule */
	if (num_rules >= MAX_NUM_RULES) {
		printk(KERN_ALERT "Could not add more mfw rules, no more space\n");
		return -ENOMEM;
	}

	/* copy_from_user returns number of bytes that COULD NOT be copied */
	if ( copy_from_user(&rule, data, sizeof(struct mfw_rule) != 0) ) {
		return -EFAULT;
	}

	memcpy(&rules[num_rules++], &rule, sizeof(struct mfw_rule));

	return (int) sizeof(struct mfw_rule);
}

int init_module() {
	nfho.hook = hook_func;
	nfho.hooknum = NF_INET_PRE_ROUTING;
	nfho.pf = PF_INET;
	nfho.priority = NF_IP_PRI_FIRST;

	nf_register_hook(&nfho);

	/* initialize proc file */
	rule_file = create_proc_entry(PROCFS_NAME, 0644, NULL);

	if (rule_file == NULL) {
		remove_proc_entry(PROCFS_NAME, NULL);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n", PROCFS_NAME);
		return -ENOMEM;
	}

	rule_file->read_proc = read_rule_file;
	rule_file->write_proc = write_rule_file;
	/* rule_file->owner = THIS_MODULE; */
	rule_file->mode = S_IFREG | S_IRUGO;
	rule_file->uid = 0;
	rule_file->gid = 0;
	rule_file->size = 37;

	printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);

	return 0;
}

void cleanup_module() {
	nf_unregister_hook(&nfho);
	remove_proc_entry(PROCFS_NAME, NULL);

	printk(KERN_INFO "mfw unloaded\n");
}
