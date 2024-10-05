class DB:
    def __init__(self) -> None:
        self.id_key = {}
        self.name_id = {}
        
    def insert(self, client_name, client_id, aes_key):
        self.name_id[client_name] = client_id
        self.id_key[client_id] = aes_key

    def exists(self, client_name="", client_id=""):
        return client_id in self.id_key and client_name in self.name_id
        