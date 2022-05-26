#include "event_system.h"

#include "internal/wldc_mem.h"
#include "data_structures/wldc_vector.h"
#include "core/logging.h"

typedef struct registered_event {
    void* listener;
    event_pfn dispatch_callback;
} registered_event;

typedef struct event_entry {
    registered_event* events;
} event_entry;

#define MAX_MESSAGE_CODES 128 * 128

typedef struct event_system_state {
    event_entry registered[MAX_MESSAGE_CODES];
} event_system_state;

static bool8 s_intialized = FALSE;
static event_system_state s_state;

bool8 initialize_event_system() {
    if (s_intialized == TRUE) {
        return FALSE;
    }
    wldc_zero_mem(&s_state, sizeof(s_state));

    s_intialized = TRUE;

    return TRUE;
}

void shutdown_event_system() {
    for (u16 i = 0; i < MAX_MESSAGE_CODES; i++) {
        if (s_state.registered[i].events != 0) {
            destroy_vector(s_state.registered[i].events);
            s_state.registered[i].events = 0;
        }
    }
}

bool8 register_event(u16 code, void* listener, event_pfn on_event) {
    if (s_intialized == FALSE) {
        return FALSE;
    }

    if (s_state.registered[code].events == 0) {
        s_state.registered[code].events = create_vector(registered_event);
    }

    u64 registered_count = get_vector_element_count(s_state.registered[code].events);
    for (u64 i = 0; i < registered_count; i++) {
        if (s_state.registered[code].events[i].listener == listener) {
            WLDC_WARN("Tried to assign the same listener to an event code more than one %s", "time!");
            return FALSE;
        }
    }

    registered_event event;
    event.listener = listener;
    event.dispatch_callback = on_event;
    // NOTE: VSCode error is not relevant
    push_to_vector(s_state.registered[code].events, event);

    return TRUE;
}
bool8 unregister_event(u16 code, void* listener, event_pfn on_event) {
    if (s_intialized == FALSE) {
        return FALSE;
    }

    if (s_state.registered[code].events == 0) {
        WLDC_WARN("Tried to unregister non-existentend %s", "event!");
        return FALSE;
    }

    u64 registered_count = get_vector_element_count(s_state.registered[code].events);
    for (u64 i = 0; i < registered_count; i++) {
        registered_event e = s_state.registered[code].events[i];
        if (e.listener == listener && e.dispatch_callback == on_event) {
            registered_event event;
            pop_at_vector(s_state.registered[code].events, i, &event);
            return TRUE;
        }
    }
    return FALSE;
}
bool8 dispatch_event(u16 code, void* sender, event_context context) {
    if (s_intialized == FALSE) {
        return FALSE;
    }

    if (s_state.registered[code].events == 0) {
        return FALSE;
    }

    u64 registered_count = get_vector_element_count(s_state.registered[code].events);
    for (u64 i = 0; i < registered_count; i++) {
        registered_event e = s_state.registered[code].events[i];
        if (e.dispatch_callback(code, sender, e.listener, context)) {
            return TRUE;
        }
    }
    return FALSE;
}
