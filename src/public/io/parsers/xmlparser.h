/**
 * @file xmlparser.h
 * @author Fox (yulefox@gmail.com)
 * @date Sep.05, 2008
 * ���ڽ��������ļ���ÿ�������ļ���Ӧһ������
 */

#ifndef PUBLIC_IO_PARSERS_XMLPARSER_H
#define	PUBLIC_IO_PARSERS_XMLPARSER_H

#include "public/log/log.h"
#include "tinyxml/tinyxml.h"

#ifdef _DEBUG
#pragma comment(lib, "tinyxml_d.lib")
#else
#pragma comment(lib, "tinyxml.lib")
#endif /* _DEBUG */

class XMLParser
{
public:
	XMLParser(const char* file, bool sync = true);
	~XMLParser();

    /// �Ƿ���سɹ�
    bool IsLoaded()
    {
        return NULL != m_root;
    }

    /// �����ļ�
    bool Save()
    {
        return m_doc->SaveFile();
    }

	/// ���ݽڵ��ι�ϵ��ȡָ���ڵ�ֵ
	const char* GetVal(const char* attr) const;

	/// ��ȡ��ǰ�ڵ�ָ������
	/// ��Ĭ��ֵ��ȱʡ��Ӧ�ó�ʼ��ʱָ��
	template<typename T>
	const char* GetAttr(const char* attr,
                        T val) const;

	/// ���õ�ǰ�ڵ�ָ������
    /// T ֧������: int, const char*
	template<typename T>
	void SetAttr(const char* attr,
                        T val) const;

    /// ��Ĭ��ֵ��ȱʡ��Ӧ�õ���ʱָ��
	template<typename T, typename CT>
	const char* GetAttr(const char* attr,
                        T val,
                        CT def) const;

	const char* GetAttr(const char* attr) const;

	/// ��ȡ��ǰ�ڵ�֮�ӽڵ�ָ������
	/// ��Ĭ��ֵ��ȱʡ��Ӧ�ó�ʼ��ʱָ��
	template <typename T>
	const char* GetChildAttr(const char* tag,
                             const char* attr,
                             T val) const;

    /// ��Ĭ��ֵ��ȱʡ��Ӧ�õ���ʱָ��
	template<typename T, typename CT>
	const char* GetChildAttr(const char* tag,
                             const char* attr,
                             T val,
                             CT def) const;

	const char* GetChildAttr(const char* tag, const char* attr) const;

	/// ��ָ��·�����õ�ǰ�ڵ�
	bool SetCursor(int count, const char* attr, ...);

	/// �ø��ڵ�Ϊ��ǰ�ڵ�
	bool SetRoot();

	/// �ø��ڵ�Ϊ��ǰ�ڵ�
	bool SetParent();

	/// ����һ�ֵܽڵ�Ϊ��ǰ�ڵ�
	bool SetPrevSibling(const char* name = NULL);

	/// ����һ�ֵܽڵ�Ϊ��ǰ�ڵ�
	bool SetNextSibling(const char* name = NULL);

	/// �����ӽڵ�Ϊ��ǰ�ڵ�
	bool SetFirstChild(const char* name = NULL);

	/// ��ĩ�ӽڵ�Ϊ��ǰ�ڵ�
	bool SetLastChild(const char* name = NULL);

    /**
     * ��ָ��index�Ľ����Ϊ��ǰ�ڵ�
     * ���ڵ�һ�������xml�ļ�������.
     * @param ind, zero-based(firstchild) index
     */
    bool SetCurNode(int ind);

    /// ɾ����ǰ�ڵ�
    void RemoveCurNode();

    /// ���뵱ǰ�ڵ��һ����������ǰ�ڵ�λ��
    void CopyAndInsertCurNode();

protected:
	/// �ⲿ������
	XMLParser();

private:
	enum CONFIG_ERROR
	{
		CE_NO_ERROR	= 0, 		///< ��ȷ
		CE_ROOT_NULL, 			///< ���ڵ�Ϊ��
		CE_PARENT_NULL, 		///< ���ڵ�Ϊ��
		CE_CURRENT_NULL, 		///< ��ǰ�ڵ�Ϊ��
		CE_PRVIOUS_NULL, 		///< ǰһ�ڵ�Ϊ��
		CE_NEXT_NULL, 			///< ��һ�ڵ�Ϊ��
		CE_FIRST_CHILD_NULL, 	///< ���ӽڵ�Ϊ��
		CE_LAST_CHILD_NULL, 	///< ĩ�ӽڵ�Ϊ��
	};

	TiXmlDocument* m_doc;
	TiXmlElement* m_root;
	TiXmlElement* m_curElem;
};

template <typename T>
const char* XMLParser::GetAttr(const char* attr,
                                 T val) const
{
	const char* res = NULL;
	if (NULL != m_curElem)
	{
		res = m_curElem->Attribute(attr, val);
	}

	if (NULL == res)
	{
		LOG_WARN("pub.io", attr);
	}

	return res;
}

template <typename T>
void XMLParser::SetAttr(const char* attr,
                                 T val) const
{
	if (NULL != m_curElem)
	{
		m_curElem->SetAttribute(attr, val);
	}
}

template <typename T, typename CT>
const char* XMLParser::GetAttr(const char* attr,
                                 T val,
                                 CT def) const
{
	const char* res = NULL;
	if (NULL != m_curElem)
	{
		res = m_curElem->Attribute(attr, val);
	}

	if (NULL == res)
	{
		*val = def;
		LOG_WARN("pub.io", "attribute[\"%s\"] not found", attr);
	}

	return res;
}

template<typename T>
const char* XMLParser::GetChildAttr(const char* tag,
                                      const char* attr,
                                      T val) const
{
	const char* res = NULL;
	TiXmlElement* childElem = NULL;
	if (NULL != m_curElem &&
		NULL != (childElem = m_curElem->FirstChildElement(tag)))
	{

		res = childElem->Attribute(attr, val);
	}

	if (NULL == res)
	{
		LOG_WARN("pub.io", "%s/%s", tag, attr);
	}

	return res;
}

template<typename T, typename CT>
const char* XMLParser::GetChildAttr(const char* tag,
                                      const char* attr,
                                      T val,
                                      CT def) const
{
	const char* res = NULL;
	TiXmlElement* childElem = NULL;
	if (NULL != m_curElem &&
		NULL != (childElem = m_curElem->FirstChildElement(tag)))
	{

		res = childElem->Attribute(attr, val);
	}

	if (NULL == res)
	{
		*val = def;
        LOG_WARN("pub.io", "%s/%s", tag, attr);
	}

	return res;
}

#endif
