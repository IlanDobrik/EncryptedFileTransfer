class DB:
    def __init__(self) -> None:
        self.db = {}
        
    def insert(self, client_id, aes_key):
        self.db[client_id] = aes_key
