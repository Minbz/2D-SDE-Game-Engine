import json
FILE_PATH = "./config.json"

def get_level_config(level_name, json_data):
    for level in json_data:
        if level["levelName"] == level_name:
            return level
    return None


def read_config(*keys):
    try:
        with open(FILE_PATH, 'r') as file:
            data = json.load(file)
            for key in keys:
                data = data[key]
            return data

    except FileNotFoundError:
        print(f"File '{FILE_PATH}' not found.")
        return None
    except json.JSONDecodeError:
        print(f"Error decoding JSON in '{FILE_PATH}'.")
        return None
    except KeyError:
        print(f"Key not found in JSON structure.")
        return None

def write_config(data, *keys):
    try:
        with open(FILE_PATH, 'r') as file:
            json_data = json.load(file)
        
        # Traverse to the nested level
        temp = json_data
        for key in keys[:-1]:
            temp = temp[key]
        
        # Update the value
        temp[keys[-1]] = data
        
        with open(FILE_PATH, 'w') as file:
            json.dump(json_data, file, indent=4)
        print(f"Data written to '{FILE_PATH}' successfully.")
    except json.JSONDecodeError:
        print(f"Error decoding JSON in '{FILE_PATH}'.")
    except Exception as e:
        print(f"Error writing data to '{FILE_PATH}': {e}")