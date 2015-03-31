#include <stdint.h>

enum mfw_rule_action { DENY, ALLOW };
enum mfw_rule_direction { IN, OUT };

struct mfw_rule {
    enum mfw_rule_action action;
    enum mfw_rule_direction direction;
    int16_t protocol;
    int16_t srcport;
    uint8_t destport;
};
