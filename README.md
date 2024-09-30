# build-JSON

## JSON Library
This is a lightweight C library for parsing, creating, manipulating, and serializing JSON objects. It supports JSON values including null, booleans, numbers, strings, arrays, and objects. The library provides functions to create, parse, modify, and free JSON data structures, as well as read from and write to files.

## Features
- Supports basic JSON types:
    - null
    - boolean
    - number
    - string
    - array
    - object
- Functions for parsing JSON strings into a JSON structure.
- Functions for creating and manipulating JSON objects, arrays, and strings.
- Ability to stringify JSON structures back into a JSON-formatted string.
- Support for reading JSON from and writing to files.
- Error handling for JSON parsing with clear error codes.
- Optimized array and object manipulation.
- Simple memory management for dynamically allocated structures.
## Requirements
  - C Standard: C11
  - Dependencies: The library uses a custom hashtable, provided by hashtable/hash_table_m.h. See: `https://github.com/PL-play/build-collection`

## Installation
To install the JSON library, follow these steps:
1. Clone the repository: 

   ```
    git clone git@github.com:PL-play/build-JSON.git
   ```
2. Build the library using CMake:
    ```
    mkdir build
    cd build
    cmake ..
    make
    sudo make install
    ```
3. Link the library in your own projects by including the headers and linking the compiled library.

## Usage
### Data Structures
- The library defines several types for representing JSON values:
- json_value: Represents any JSON value, including null, booleans, numbers, strings, arrays, and objects.
- json_string: Represents a string in JSON.
- json_array: Represents a JSON array, storing elements of type json_value.
- json_obj: A hashtable-based representation of JSON objects, storing key-value pairs.

## Example: Creating a JSON Object
  Here's an example of how to create and manipulate a JSON object:
  ```
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
  ```

## Example: Parsing JSON
You can parse a JSON-formatted string into a json_value structure using parse_json_string:
```
  json_value value;
  const char *json_str = "{\"name\":\"John\", \"age\":30}";

  int result = parse_json_string(&value, json_str);

  if (result == JSON_PARSE_OK) {
      // Successfully parsed the JSON
      const char *name = get_json_str(get_json_object_value(&value, "name", 4));
      json_number age = get_json_number(get_json_object_value(&value, "age", 3));
      printf("Name: %s, Age: %.0f\n", name, age);
  } else {
      printf("Failed to parse JSON\n");
  }

  // Free memory
  free_json_value(&value);
```

## Example: Reading and Writing JSON Files
Writing JSON to a file:
```
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


  int result = json_dump(&obj, "output.json");
  if (result == JSON_DUMP_OK) {
      printf("JSON dumped to file successfully.\n");
  } else {
      printf("Failed to dump JSON to file.\n");
  }

  free_json_value(&obj);
```
Reading JSON from a file:
```
  json_value value;

  int result = json_load(&value, "input.json");
  if (result == JSON_PARSE_OK) {
      printf("JSON loaded successfully.\n");
      // Process JSON...
  } else {
      printf("Failed to load JSON.\n");
  }
  size_t len;
  char *json_str = json_stringify(&value, &len);
  printf("%s.\n", json_str);
  printf("json string length: %lu.\n", len);
  free(json_str);
  free_json_value(&value);
```

## API Overview
### Creating JSON Values
- json_value *new_null(): Creates a new JSON null value.
- void set_json_number(json_value *, double n): Sets a json_value to a number.
- void set_json_str(json_value *, const char *, size_t): Sets a json_value to a string.
- void set_json_bool(json_value *, int): Sets a json_value to a boolean.
### Parsing and Stringifying
- int parse_json_string(json_value *, const char *json): Parses a JSON string.
- char *json_stringify(const json_value *value, size_t *len): Converts a json_value to a JSON-formatted string. 
### Array Manipulation
- json_value *insert_json_array(json_value *value, size_t index): Inserts an element into a JSON array at the specified index.
- void remove_json_array_element(json_value *value, size_t start, size_t count): Removes elements from a JSON array.
### Object Manipulation
- json_value *set_json_object(json_value *v, char *key, size_t key_len, int *is_new): Adds or updates a key-value pair in a JSON object.
- int remove_json_object(json_value *v, char *key, size_t key_len): Removes a key-value pair from a JSON object.
### File Operations
- int json_dump(const json_value *value, char *fp): Writes a json_value to a file.
- int json_load(json_value *value, char *fp): Loads a JSON structure from a file.
### Error Codes
- Parsing errors:
  - JSON_PARSE_OK: Parsing succeeded.
  - JSON_PARSE_INVALID_VALUE: Invalid value encountered during parsing.
  - JSON_PARSE_MISS_KEY: A key is missing in the object.
  - Full list of parsing errors available in json.h.
- File errors:
  - JSON_DUMP_FILE_ERROR: Failed to write to file.
  - JSON_LOAD_FILE_ERROR: Failed to load from file.
  
## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.