SERVER_VERSION = 1
CLIENT_ID_SIZE = 16



CONFIG_FILE_PATH = "./port.info"

class Config:
    def __init__(self, port=1256):
        self.port = port


def read_config() -> Config:
    config = Config()
    try:
        with open(CONFIG_FILE_PATH, "r") as f:
            contents = f.readlines()
        config.port = int(contents[0].strip())
    except:
        pass
    
    return config
