#include "AESEncryption.h"

#include "cryptopp\aes.h"
#include "cryptopp\rng.h"
#include "cryptopp\modes.h"
#include "cryptopp\filters.h"

constexpr unsigned int DEFAULT_KEYLENGTH = 32;


AES::AES(const Buffer& key, const Buffer& iv) :
    m_key(key), m_iv(Buffer(CryptoPP::AES::BLOCKSIZE, 0))
{ }

Buffer AES::encrypt(const Buffer& input) {
	CryptoPP::AES::Encryption aesEncryption(m_key.data(), DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, m_iv.data());

	Buffer cipher;
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::VectorSink(cipher));
	stfEncryptor.Put(input.data(), input.size());
	stfEncryptor.MessageEnd();

	return cipher;
}

Buffer AES::decrypt(const Buffer& input) {

	CryptoPP::AES::Decryption aesDecryption(m_key.data(), DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, m_iv.data());

	Buffer plain;
	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::VectorSink(plain));
	stfDecryptor.Put(input.data(), input.size());
	stfDecryptor.MessageEnd();

	return plain;
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

Buffer AES::getKey() const
{
	return m_key;
}
