#include "AESEncryption.hpp"

#include "aes.h"
#include "rng.h"
#include "base64.h"
#include "modes.h"
#include "filters.h"

constexpr unsigned int DEFAULT_KEYLENGTH = 16;


AES::AES(const Buffer& key, const Buffer& iv) :
    m_key(key), m_iv(Buffer(CryptoPP::AES::BLOCKSIZE, 0))
{ }

Buffer AES::encrypt(const Buffer& input) {
	CryptoPP::AES::Encryption aesEncryption(m_key.data(), DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, m_iv.data());

	Buffer cipher;
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::VectorSink(cipher));
	stfEncryptor.Put(cipher.data(), cipher.size());
	stfEncryptor.MessageEnd();

	return cipher;
}

Buffer AES::decrypt(const Buffer& input) {

	CryptoPP::AES::Encryption aesEncryption(m_key.data(), DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcDecryption(aesEncryption, m_iv.data());

	Buffer cipher;
	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::VectorSink(cipher));
	stfDecryptor.Put(cipher.data(), cipher.size());
	stfDecryptor.MessageEnd();

	return cipher;
}


Buffer AES::GenerateKey()
{
	Buffer out(DEFAULT_KEYLENGTH, 0);
	
	for (auto& b : out) {
		if (0 == _rdrand32_step(reinterpret_cast<unsigned int*>(&b))) {
			throw std::exception("Failed to generate key");
		}
	}

	return out;
}