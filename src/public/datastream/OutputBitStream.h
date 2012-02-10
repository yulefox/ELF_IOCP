#pragma once

#define OUTPUT_DOT_COUNT 2047//2kÿ��

class OutputBitStream
{
	std::vector<uchar>m_byStreamArray;

	uchar m_byMask;
    int m_iRack;

	int m_iOutputDotCount;

	int m_iStreamPosition;

public:
	OutputBitStream(void);
	~OutputBitStream(void);

	void OutputBit(int bit);
	void OutputBits(unsigned int dwCode, int iCount);
	int  GetLength() const { return (int)m_byStreamArray.size();}// �������ֽڳ���

	void Flush() { m_iStreamPosition = 0;}
	uchar GetChar() { return m_byStreamArray[m_iStreamPosition++];}

	void CloseStream(void);
	void OpenStream(void);
};
