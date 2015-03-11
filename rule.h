enum { DENY, ALLOW } mfw_rule_action;
enum { IN, OUT } mfw_rule_direction;
enum { TCP, UDP, ALL } mfw_rule_protocol;


struct mfw_rule {
    enum mfw_rule_action action;
    enum mfw_rule_direction direction;
    enum mfw_rule_protocol protocol;
    uint8_t srcport;
    uint8_t destport;
};
