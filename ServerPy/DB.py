import sqlite3
import datetime

class ClientsRow:
    def __init__(self, *args):
        self.client_id = args[0]
        self.client_name = args[1]
        self.public_key = args[2]
        self.last_seen = args[3]
        self.aes_key = args[4]

class FilesRow:
    def __init__(self, *args):
        self.client_id = args[0]
        self.file_name = args[1]
        self.path_name = args[2]
        self.verified = args[3]

class DB:
    CREATE_CLIENTS_TABLE = '''CREATE TABLE IF NOT EXISTS "Clients" (
	"ID"	    BLOB,
	"Name"	    TEXT UNIQUE NOT NULL,
	"PublicKey"	BLOB,
	"LastSeen"	TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	"AesKey"	BLOB,
	PRIMARY KEY("ID")
);'''
    CREATE_FILES_TABLE = '''CREATE TABLE IF NOT EXISTS "Files" (
	"ID"	    BLOB,
	"FileName"	TEXT,
	"PathName"	TEXT,
	"Verified"	BOOLEAN,
	PRIMARY KEY("ID", "FileName"),
    FOREIGN KEY(ID) REFERENCES Clients(ID)
);'''
    
    INSERT_CLIENT = '''INSERT OR REPLACE INTO Clients VALUES(?, ?, ?, ?, ?)'''
    INSERT_FILE = '''INSERT OR REPLACE INTO files VALUES(?, ?, ?, ?)'''
    
    GET_CLIENT = '''SELECT * FROM Clients WHERE ID=? AND Name=?'''
    GET_FILE = '''SELECT * FROM Files WHERE ID=?'''
    
    CHECK_CLIENT_NAME = '''SELECT * FROM Clients WHERE Name=?'''
    
    
    def __init__(self, path):
        self.conn = sqlite3.connect(path, check_same_thread=False)
        self.cursor = self.conn.cursor()
        
        self.create_tables()

    def __enter__(self):
        return self
    
    def __exit__(self, exception_type, exception_value, exception_traceback):
        self.conn.commit()
        self.conn.close()
        
    def create_tables(self):
        self.cursor.execute(self.CREATE_CLIENTS_TABLE)
        self.cursor.execute(self.CREATE_FILES_TABLE)
        self.conn.commit()
        
    def insert_client(self, client_id, client_name, public_key, aes_key):
        last_seen = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.cursor.execute(self.INSERT_CLIENT, (client_id, client_name, public_key, last_seen, aes_key))
        self.conn.commit()
        
    def insert_file(self, id, filename, path, verified=False):
        self.cursor.execute(self.INSERT_FILE, (id, filename, path, verified))
        self.conn.commit()

    def get_client(self, client_id, client_name) -> ClientsRow:
        res = self.cursor.execute(self.GET_CLIENT, (client_id, client_name,)).fetchone()
        if res == None:
            return None
        return ClientsRow(*res)
    
    def get_file(self, client_id) -> FilesRow:
        res = self.cursor.execute(self.GET_FILE, (client_id, )).fetchone()
        if res == None:
            return None
        return FilesRow(*res)

    def exists(self, client_id, client_name):
        return self.get_client(client_id, client_name) is not None
    
    def name_exists(self, client_name):
        return self.cursor.execute(self.CHECK_CLIENT_NAME, (client_name, )).fetchone() is not None
