#include <stdint.h>

enum mfw_rule_action { DENY, ALLOW };
enum mfw_rule_direction { IN, OUT };

struct mfw_rule {
    enum mfw_rule_action action;
    enum mfw_rule_direction direction;
    int8_t protocol;
    uint16_t srcport;
    uint16_t destport;
};
