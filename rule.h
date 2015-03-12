enum { DENY, ALLOW } mfw_rule_action;
enum { IN, OUT } mfw_rule_direction;

struct mfw_rule {
    enum mfw_rule_action action;
    enum mfw_rule_direction direction;
    uint8_t protocol;
    uint8_t srcport;
    uint8_t destport;
};
