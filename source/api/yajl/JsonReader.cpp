#include "Defines.hpp"

#if I9_USE_JSON == 1

#include "api/yajl/JsonReader.hpp"
#include "util/Log.hpp"

#define TAG "[JsonReader] "

namespace Sascar {

JsonReader::JsonReader()
	: pRootNode(nullptr)
	, pCurNode(nullptr)
	, pCurArray(nullptr)
	, qStackNode()
	, qStackArray()
	, qStackArrayPos()
	, iPos(0)
{
}

JsonReader::~JsonReader()
{
	yajl_tree_free(pRootNode);
	pRootNode = nullptr;
	pCurNode = nullptr;
	pCurArray = nullptr;
	iPos = 0;
}

JsonReader::JsonReader(const JsonReader &other)
	: IReader(other)
	, pRootNode(nullptr)
	, pCurNode(other.pCurNode)
	, pCurArray(other.pCurArray)
	, qStackNode()
	, qStackArray()
	, qStackArrayPos()
	, iPos(other.iPos)
{
}

JsonReader::JsonReader(const yajl_val node)
	: pRootNode(nullptr)
	, pCurNode(node)
	, pCurArray(nullptr)
	, qStackNode()
	, qStackArray()
	, qStackArrayPos()
	, iPos(0)
{
}

JsonReader &JsonReader::operator=(const JsonReader &other)
{
	if (this != &other)
	{
		pRootNode = nullptr;
		pCurNode = other.pCurNode;
		pCurArray = other.pCurArray;
		iPos = other.iPos;
	}

	return *this;
}

bool JsonReader::Load(const void *data)
{
	I9_ASSERT(data);
	bool ret = false;
	char err[1024];

	//fprintf(stdout, "\n\nJSON: %s\n\n", (char *)data);
	yajl_tree_free(pRootNode);
	pCurNode = pRootNode = yajl_tree_parse((const char *)data, err, sizeof(err));

	if (pCurNode != nullptr)
	{
		ret = true;
	}
	else
	{
		if (strlen(err))
		{
			Log(TAG "Error: %s", err);
		}
		else
		{
			Log(TAG "Error: unknown.");
		}
	}

	return ret;
}

bool JsonReader::Load(IReader &reader)
{
	bool ret = false;

	yajl_tree_free(pRootNode);
	pCurNode = static_cast<const JsonReader *>(&reader)->pCurNode;
	pCurArray = static_cast<const JsonReader *>(&reader)->pCurArray;
	iPos = static_cast<const JsonReader *>(&reader)->iPos;

	if (pCurNode != nullptr)
		ret = true;

	return ret;
}

const char *JsonReader::ReadString(const char *key, const char *value) const
{
	const char *ret = value;

	const char *path[] = {key, (const char *)0};
	yajl_val v = yajl_tree_get(pCurNode, path, yajl_t_string);
	if (v && YAJL_IS_STRING(v))
		ret = YAJL_GET_STRING(v);

	return ret;
}

u32 JsonReader::ReadU32(const char *key, u32 value) const
{
	u32 ret = value;

	const char *path[] = {key, (const char *)0};
	yajl_val v = yajl_tree_get(pCurNode, path, yajl_t_number);
	if (v && YAJL_IS_INTEGER(v))
		ret = (u32)YAJL_GET_INTEGER(v);
//	else
//		Log(TAG "Error reading a u32 for key %s", key);

	return ret;
}

u32 JsonReader::GetU32(u32 value) const
{
	u32 ret = value;

	yajl_val v = pCurNode;
	if (v && YAJL_IS_INTEGER(v))
		ret = (u32)YAJL_GET_INTEGER(v);

	return ret;
}

const char *JsonReader::GetKey(u32 atPos) const
{
	if (YAJL_IS_OBJECT(pCurNode) && pCurNode->u.object.len > atPos)
		return  pCurNode->u.object.keys[atPos];

	return nullptr;
}

s32 JsonReader::ReadS32(const char *key, s32 value) const
{
	s32 ret = value;

	const char *path[] = {key, (const char *)0};
	yajl_val v = yajl_tree_get(pCurNode, path, yajl_t_number);
	if (v && YAJL_IS_INTEGER(v))
		ret = (s32)YAJL_GET_INTEGER(v);
//	else
//		Log(TAG "Error reading a s32 for key %s", key);

	return ret;
}

f32 JsonReader::ReadF32(const char *key, f32 value) const
{
	f32 ret = value;

	const char *path[] = {key, (const char *)0};
	yajl_val v = yajl_tree_get(pCurNode, path, yajl_t_number);
	if (v && YAJL_IS_DOUBLE(v))
		ret = (f32)YAJL_GET_DOUBLE(v);
//	else
//		Log(TAG "Error reading a f32 for key %s", key);

	return ret;
}

bool JsonReader::ReadBool(const char *key, bool value) const
{
	const char *path[] = {key, (const char *)0};
	yajl_val v = yajl_tree_get(pCurNode, path, yajl_t_true);

	bool ret = value;
	if (v)
		ret = YAJL_IS_TRUE(v);

	return ret;
}

u32 JsonReader::SelectArray(const char *key)
{
	const char *path[] = {key, (const char *)0};
	yajl_val v = yajl_tree_get(pCurNode, path, yajl_t_array);

	u32 len = 0;
	if (YAJL_IS_ARRAY(v))
	{
//		Log(TAG "Array %s found, len: %ld", key, YAJL_GET_ARRAY(v)->len);
		qStackNode.push(pCurNode);
		qStackArray.push(pCurArray);
		qStackArrayPos.push(iPos);
		pCurArray = v;
		iPos = 0;
		len = (u32)YAJL_GET_ARRAY(v)->len;
	}
//	else
//		Log(TAG "Array %s not found", key);

	return len;
}

void JsonReader::SelectNext()
{
	if (pCurArray && (iPos < YAJL_GET_ARRAY(pCurArray)->len))
	{
		pCurNode = YAJL_GET_ARRAY(pCurArray)->values[iPos];
		iPos++;
	}
}

void JsonReader::UnselectArray()
{
	if (!qStackArray.empty())
	{
		pCurArray = qStackArray.top();
		qStackArray.pop();

		iPos = qStackArrayPos.top();
		qStackArrayPos.pop();

		if (!qStackNode.empty())
		{
			pCurNode = qStackNode.top();
			qStackNode.pop();
		}
	}
}

bool JsonReader::IsNode(const char *key) const
{
	const char *path[] = {key, (const char *)0};
	yajl_val v = yajl_tree_get(pCurNode, path, yajl_t_object);

	return YAJL_IS_OBJECT(v);
}

bool JsonReader::SelectNode(const char *key)
{
	const char *path[] = {key, (const char *)0};
	yajl_val v = yajl_tree_get(pCurNode, path, yajl_t_object);
	bool ret = false;
	if (YAJL_IS_OBJECT(v))
	{
//		Log(TAG "Node %s found", key);
		qStackNode.push(pCurNode);
		pCurNode = v;
		ret = true;
	}
//	else
//		Log(TAG "Node %s not found", key);

	return ret;
}

void JsonReader::UnselectNode()
{
	if (!qStackNode.empty())
	{
		pCurNode = qStackNode.top();
		qStackNode.pop();
	}
}

}

#endif // SEED_USE_JSON
