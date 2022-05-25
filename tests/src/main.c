#include <wildcard/core/application.h>

#include "game.h"

int main(void) {
    application_props props;

    props.width = 1280;
    props.height = 720;
    props.title = "WildCard Engine Testing";

    props.app_init_pfn = game_init;
    props.app_update_pfn = game_update;
    props.app_shtdown_pfn = game_shutdown;

    app_init(&props);
    app_run();
}