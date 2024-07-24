#include <string.h>

#include "caps_word.h"
#include "debug.h"
#include "transactions.h"

typedef struct _master_to_slave_t {
    bool is_caps_word_on :1;
} master_to_slave_t;

master_to_slave_t sync_data;

void user_config_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer,
                      uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(master_to_slave_t)) {
        memcpy(&sync_data, initiator2target_buffer, initiator2target_buffer_size);
    }
}

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    // if buffer length matches size of data structure (simple error checking)
    if (in_buflen == sizeof(sync_data)) {
        // copy data from master into local data structure
        memcpy(&sync_data, in_data, in_buflen);
    }
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            master_to_slave_t m2s = { .is_caps_word_on = is_caps_word_on() };
            if (transaction_rpc_send(USER_SYNC_A, sizeof(master_to_slave_t), &m2s)) {
                last_sync = timer_read32();
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    } else { // slave side
        if (sync_data.is_caps_word_on) {
            caps_word_on();
        } else {
            caps_word_off();
        }
    }
}
