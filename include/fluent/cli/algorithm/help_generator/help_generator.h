/*
    The Fluent Programming Language
    -----------------------------------------------------
    This code is released under the GNU GPL v3 license.
    For more information, please visit:
    https://www.gnu.org/licenses/gpl-3.0.html
    -----------------------------------------------------
    Copyright (c) 2025 Rodrigo R. & All Fluent Contributors
    This program comes with ABSOLUTELY NO WARRANTY.
    For details type `fluent l`. This is free software,
    and you are welcome to redistribute it under certain
    conditions; type `fluent l -f` for details.
*/

//
// Created by rodrigo on 5/16/25.
//

#ifndef HELP_GENERATOR_H
#define HELP_GENERATOR_H

#include <ankerl/unordered_dense.h>
#include <memory>

#include "../../flag/flag.h"
#include "../padding/padding.h"

namespace fluent::cli
{
    inline void generate_help(
        const char *name,
        const char *desc,
        const ankerl::unordered_dense::map<std::string, std::shared_ptr<Flag>>& flags,
        const size_t padding = 15
    )
    {
        // We can use the C print implementation directly, no need to use the mutexed
        // version here, as this is supposed to happen on startup
        printf("%s", name);
        printf(" - ");
        printf("%s\n", desc);
        puts("");
        puts("AVAILABLE FLAGS:");

        // Iterate over the flags and print them all
        for (auto &[key, value] : flags)
        {
            // Ignore shortcuts
            if (key == value->shortcut)
            {
                continue;
            }

            // Print the flag info
            printf("--");
            string_builder_t key_builder;
            init_string_builder(&key_builder, 25);
            write_string_builder(&key_builder, key.data());

            // Print shortcuts
            if (!value->shortcut.empty())
            {
                write_string_builder(&key_builder, ", -");
                write_string_builder(&key_builder, value->shortcut.data());
            }

            print_padding(collect_string_builder_no_copy(&key_builder), padding);
            destroy_string_builder(&key_builder);

            printf("%s", value->desc.data());

            // Print the flag metadata
            if (value->type == STRING)
            {
                printf(" (STRING)");
            }

            if (value->required)
            {
                printf(" (REQUIRED)");
            }
            puts("");
        }
    }
}

#endif //HELP_GENERATOR_H
