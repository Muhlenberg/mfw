#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>

#define PROC_FS_MAX 1024

static struct nf_hook_ops nfho;
static struct proc_dir_entry *rule_file;
static char procfs_buffer[PROC_FS_MAX];
static int proc_buffer_size = 0;

ssize_t read_callback (struct file *fp, char *d, size_t len, loff_t *l) {
		return sizeof(char);
}

ssize_t write_callback (struct file *fp, const char *d, size_t len, loff_t *l) {
	return sizeof(char);
}

int open_callback (struct inode *n, struct file *fp) {
	return 0;
}

int release_callback (struct inode *n, struct file *fp) {
	return 0;
}

static const struct file_operations proc_file_fops = {
	.owner = THIS_MODULE,
	.open = open_callback,
	.read = read_callback,
	.write = write_callback,
	.release = release_callback,
};

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
        struct mfw_rule* rule = rules[i];
        int i=0;
        for (i; i < rules.length; i++) {

            ip_header = (stuct iphdr *)skb_network_header(socket_buff); // Network header

            // If the packet's protocol matches the rule
            if (ip_header->protocol == rule->protocol || ip_header->protocol == -1) {
                if (rule->mfw_rule_action == ALLOW) {
                    return NF_ACCEPT;
                else (rule->mfw_rule_action == DENY) {
                    return NF_DROP;
                }
            } else if (ip_header) {
            }
    }
}

int init_module() {
	nfho.hook = hook_func;
	nfho.hooknum = NF_INET_PRE_ROUTING;
	nfho.pf = PF_INET;
	nfho.priority = NF_IP_PRI_FIRST;

	nf_register_hook(&nfho);
	return 0;
}

void cleanup_module() {
	nf_unregister_hook(&nfho);
}
