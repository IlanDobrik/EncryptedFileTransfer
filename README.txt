Video:
https://drive.google.com/file/d/1InF3IIgkLyCXl-UBBmTNxTA0UIvFsMfc/view?usp=drive_link

In client i have encrypted each packet, then sent to server.
Each packet is limited to 1GB, if there is 1.5GB file, 1GB will be sent, then 0.5GB
In me.info 3rd line i have saved AES key agreed with server

Place Boost & CryptoPP like this:
MMN15
	* ClientCPP/
	* ServerPy/
cryptopp890/
	*cryptopp/
		* base64.h
		* aes.h
		...
boost_1_86_0/
	* boost/
	* doc/
	* libs/
	...
