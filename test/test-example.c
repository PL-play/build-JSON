//
// Created by ran on 24-9-30.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "help_test/framework.h"
#include "zjson.h"

/**
*   Example: Creating a JSON Object
*   Here's an example of how to create and manipulate a JSON object:
 */
static void test_create() {
    json_value obj;
    init_as_object(&obj);

    // Add a number
    json_value *n = set_json_object_sk(&obj, "pi");
    set_json_number(n, 3.1415926);

    // Add a string
    json_value *name = set_json_object_sk(&obj, "name");
    set_json_str_sk(name, "Ran");

    // Create an array
    // Add array to object
    json_value *numbers = set_json_object_sk(&obj, "numbers");
    init_as_array(numbers, 0);
    set_json_number(insert_json_array_last(numbers), 1.0);
    set_json_number(insert_json_array_last(numbers), 2.0);
    set_json_number(insert_json_array_last(numbers), 3.0);

    // Stringify and print the JSON object
    size_t json_len;
    char *json_str = json_stringify(&obj, &json_len);
    printf("%s\n", json_str);

    // Free memory
    free(json_str);
    free_json_value(&obj);
}

static UnitTestFunction tests[] = {
    test_create,
    NULL
};

int main(int argc, char *argv[]) {
    run_tests(tests);
    return 0;
}
