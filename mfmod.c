#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static struct nf_hook_ops nfho;

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
