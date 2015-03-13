enum mfw_rule_action { DENY, ALLOW };
enum mfw_rule_direction { IN, OUT };

struct mfw_rule {
    enum mfw_rule_action action;
    enum mfw_rule_direction direction;
    uint8_t protocol;
    uint8_t srcport;
    uint8_t destport;
};
