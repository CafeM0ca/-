#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP


#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message
{
public:
	enum { header_length = 4 };
	enum { max_body_length = 512 };

	chat_message() : body_length_(0)			// data_의 몸통길이 0
	{
	}

	const char* data() const		
	{
		return data _;							// return 하는 data_를 읽기용으로 반환
	}

	char* data() 
	{
		return data_;							// return 하는 data_를 쓰기용으로 반환
	}

	std::size_t length() const
	{
		return header_length + body_length_;	// data_의 크기
	}

	const char* body() const
	{
		return data_ + header_legnth;
	}

	char *body()
	{
		return data_ + header_length;
	}

	void body_length(std::size_t new_length)
	{
		body_length_ = new_length;				
		if (body_length_ > max_body_length)		// body의 길이가 최대길이보다 크면 최대길이까지 짜름
			body_length_ = max_body_length;
	}

	bool decode_header()
	{
		char header[header_length + 1] = "";
		std::strncat(header, data_, header_length);	   // data_의 해더부분을 복사 
		body_length = std::atoi(header);
		if(body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}

	void encode_header()
	{
		char header[header_length + 1] = "";
		std::sprintf(header, "%4d", static_cast<int>(body_length_));		// leng이 333이면 header에 " 333"으로 들어감
		std::memcpy(data_, header, header_length);							// 헤더부분 복사
	}
private:
	char data_[header_length + max_body_length];						//data_의 크기는 헤더와 message로 구성
	std::size_t body_length_;											//message의 데이터 내용
};

#endif
