#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static struct nf_hook_ops nfho;

unsigned int hook_func_inc(unsigned int hooknum,
	struct sk_buff *skb,
	const struct net_device *in,
	const struct net_device *out,
	int (*okfn)(struct sk_buff *))
{
    if (!skb) return NF_ACCEPT;

    iph = ip_hdr(skb);
    if (!iph) return NF_ACCEPT;

    struct mfw_rule* rule;
    uint8_t i=0;
    for (i; i < MAX_NUM_RULES; i++) {
        // Get next rule
        if (rules[i] == NULL) {
            break; // End of rules
        } else if (rules[i]->direction  != IN) {
            continue; // Incoming traffic only
        } else {
            rule = rules[i];
        }

        uint16_t srcport = (struct tcphdr*) (((uint16_t*) iph) + iph->ihl * 4);
        srcport = ntohs(srcport);
        printk("Incoming src port: " + srcport);

        //uint16_t dport = (struct tcphdr*) (((uint16_t*) iph) + iph->ihl * 4 + 16);
        dport = ntohs(dport);


        if (rule->protocol == All) {
            //if (iph->protocol == IPPROTO_TCP) {
            //    uint16_t tcph = tcp_hdr(skb); // Might not work b/c tcp header isnt set
            //    dst_port = ntohs(tcph->dest);
            //} else if (iph->protocol == IPPROTO_UDP) {

            //}
            //return rule->action == ALLOW ? NF_ACCEPT : NF_DROP;
        } else if (rule->protocol == IPPROTO_TCP) {
            return rule->action == ALLOW ? NF_ACCEPT : NF_DROP;
        } else if (rule->protocol == IPPROTO_UDP) {
            return rule->action == ALLOW ? NF_ACCEPT : NF_DROP;
        }

    } // End Loop 

    // If the packet didnt get filtered out by any rules
    return NF_ACCEPT;
}

int init_module() {
	nfho.hook = hook_func_inc;
	nfho.hooknum = NF_INET_PRE_ROUTING;
	nfho.pf = PF_INET;
	nfho.priority = NF_IP_PRI_FIRST;

	nf_register_hook(&nfho);

	//nfho.hook = hook_func_out;
	//nf_register_hook(&nfho);
	return 0;
}

void cleanup_module() {
	nf_unregister_hook(&nfho);
}
