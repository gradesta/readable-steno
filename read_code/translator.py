import json, sys

SPECIAL_CHARACTERS = "\\\"\'"

with open(f'{sys.argv[1].split(".")[0]}.json', 'r') as file:
    data = json.load(file)



with open(f'{sys.argv[1].split(".")[0]}.h', 'w') as f:
    print("""#include <stdlib.h>
typedef struct {
    const char *chord;
    const char *output;
} Entry;
          
typedef struct {
    const Entry *steno_entries;
    const uint32_t size;    
} Dictionary;

const Entry steno_entries[] = {""", 
    file = f)
    
    for chord, output in data.items():

        # for char in SPECIAL_CHARACTERS:
        #     chord = chord.replace(char, "\\"+char)
        
        for char in SPECIAL_CHARACTERS:
            output = output.replace(char, "\\"+char)

        print(f"    {{ \"{chord}\", \"{output}\" }},", file = f)

    print("    { NULL, NULL }", file = f)
    print("};", file = f)

    print(f"""
const Dictionary steno_dict = {{ steno_entries, {len(data)} }};
          """, file=f)