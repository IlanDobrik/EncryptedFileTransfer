class DB:
    def __init__(self) -> None:
        self.id_key = {}
        self.name_id = {}
        
    def insert(self, client_name, client_id, public_key):
        self.name_id[client_name] = client_id
        self.id_key[client_id] = public_key

    def get(self, client_id):
        return self.id_key[client_id]

    def exists(self, client_name):
        return client_name in self.name_id
        