#pragma once
#include <string>

#include "../include/chakra/ChakraCore.h"
#include "DllHelper.h"
#include <optional>

#ifndef DECL_API
#define DECL_API(f) decltype(f)* f##_ = _dll[#f]
#endif

class ChakraApi {
	DllHelper _dll{"Chakra.dll"};

public:
	DECL_API(JsCreateRuntime);
	DECL_API(JsCreateContext);
	DECL_API(JsSetCurrentContext);
	DECL_API(JsDisposeRuntime);
	DECL_API(JsRunScript);
	DECL_API(JsConvertValueToString);
	DECL_API(JsStringToPointer);
	DECL_API(JsSetRuntimeMemoryLimit);
	DECL_API(JsCreateObject);
	DECL_API(JsGetGlobalObject);
	DECL_API(JsGetPropertyIdFromName);
	DECL_API(JsPointerToString);
	DECL_API(JsSetProperty);
	DECL_API(JsCreateFunction);
	DECL_API(JsCreateString);
	DECL_API(JsHasException);
	DECL_API(JsGetAndClearException);
	DECL_API(JsCollectGarbage);
	DECL_API(JsAddRef);
	DECL_API(JsRelease);
	DECL_API(JsGetNullValue);
	DECL_API(JsCreateExternalObject);
	DECL_API(JsGetCurrentContext);
	DECL_API(JsGetExternalData);
	DECL_API(JsGetUndefinedValue);
	DECL_API(JsStrictEquals);
	DECL_API(JsGetValueType);
	DECL_API(JsHasExternalData);
	DECL_API(JsBoolToBoolean);
	DECL_API(JsCreateError);
	DECL_API(JsSetException);
	DECL_API(JsCreateTypeError);
	DECL_API(JsDefineProperty);
	DECL_API(JsGetTrueValue);
	DECL_API(JsGetFalseValue);
	DECL_API(JsDoubleToNumber);
	DECL_API(JsNumberToDouble);
	DECL_API(JsSetPrototype);
	DECL_API(JsGetProperty);
	DECL_API(JsBooleanToBool);
	DECL_API(JsCallFunction);
	DECL_API(JsDisableRuntimeExecution);
	DECL_API(JsCreateArray);
	DECL_API(JsIntToNumber);
	DECL_API(JsSetIndexedProperty);
	DECL_API(JsNumberToInt);
	DECL_API(JsGetIndexedProperty);

	std::wstring exceptionToString(JsValueRef ref) {
		JsValueRef stack;
		getProperty(ref, L"stack", &stack);
		if (isNullOrUndefined(stack))
			return valueToString(ref);
		else
			return valueToString(stack);
	}

	void throwException(std::wstring error) {
		JsValueRef errorValue;
		JsValueRef errorObject;
		JsPointerToString_(error.c_str(), error.length(), &errorValue);
		JsCreateError_(errorValue, &errorObject);
		JsSetException_(errorObject);
	}

	void throwTypeException(std::wstring error) {
		JsValueRef errorValue;
		JsValueRef errorObject;
		JsPointerToString_(error.c_str(), error.length(), &errorValue);
		JsCreateTypeError_(errorValue, &errorObject);
		JsSetException_(errorObject);
	}

	JsValueRef toBoolean(bool boolVal) {
		JsValueRef ref = JS_INVALID_REFERENCE;
		JsBoolToBoolean_(boolVal, &ref);
		return ref;
	}

	JsValueRef toNumber(double doubleVal) {
		JsValueRef ref = JS_INVALID_REFERENCE;
		JsDoubleToNumber_(doubleVal, &ref);
		return ref;
	}

	JsValueRef trueValue() {
		JsValueRef ref = JS_INVALID_REFERENCE;
		JsGetTrueValue_(&ref);
		return ref;
	}

	JsValueRef falseValue() {
		JsValueRef ref = JS_INVALID_REFERENCE;
		JsGetFalseValue_(&ref);
		return ref;
	}

	JsValueRef nullValue() {
		JsValueRef ref = JS_INVALID_REFERENCE;
		JsGetNullValue_(&ref);
		return ref;
	}

	std::optional<JsValueRef> tryGetFunctionFromArgs(JsValueRef arg, int argumentCount) {
		if (argumentCount < 1)
			return std::optional <JsValueRef>();

		JsValueType type = JsUndefined;
		JsGetValueType_(arg, &type);

		if (type != JsFunction)
			return std::optional<JsValueRef>();

		return arg;
	}

	std::optional<std::wstring> tryGetStringFromArgs(JsValueRef args, int argumentCount) {
		if (argumentCount < 1)
			return std::optional<std::wstring>();

		const wchar_t* ref = 0;
		size_t length = 0;
		auto err = JsStringToPointer_(args, &ref, &length); 
		if (err != JsNoError)
			return std::optional<std::wstring>();
		return std::optional<std::wstring>(std::wstring(ref, length));
	}

	std::optional<bool> tryGetBoolFromArgs(JsValueRef* args, int argumentCount) {
		if (argumentCount < 1)
			return std::optional<bool>();

		bool ref = false;
		auto err = JsBooleanToBool_(args[0], &ref);
		if (err != JsNoError)
			return std::optional<bool>();
		return ref;
	}

	JsValueRef defineFunction(JsValueRef object, const wchar_t* callbackName, JsNativeFunction function, void* callbackState = nullptr) {
		JsPropertyIdRef propertyId;
		JsGetPropertyIdFromName_(callbackName, &propertyId);

		JsValueRef functionRef;
		JsCreateFunction_(function, callbackState, &functionRef);

		JsSetProperty_(object, propertyId, functionRef, true);

		return functionRef;
	}

	void addPropertyToObj(JsValueRef obj, const wchar_t* name, JsValueRef prop) {
		JsPropertyIdRef propertyId;
		JsGetPropertyIdFromName_(name, &propertyId);
		JsSetProperty_(obj, propertyId, prop, true);
	}

	bool defineValueProp(JsValueRef object, const wchar_t* name, JsValueRef value, bool changeable) {
		JsPropertyIdRef namePropertyId;
		JsGetPropertyIdFromName_(name, &namePropertyId);

		JsValueRef propertyDesc;
		JsCreateObject_(&propertyDesc);

		JsValueRef jsTrue;
		JsGetTrueValue_(&jsTrue);
		JsValueRef jsFalse;
		JsGetFalseValue_(&jsFalse);

		addPropertyToObj(propertyDesc, L"value", value);
		addPropertyToObj(propertyDesc, L"writable", jsFalse);
		addPropertyToObj(propertyDesc, L"enumerable", jsTrue);
		addPropertyToObj(propertyDesc, L"configurable", jsFalse);

		bool result;
		JsDefineProperty_(object, namePropertyId, propertyDesc, &result);
		return result;
	}

	bool defineProp(JsValueRef object, const wchar_t* name, JsNativeFunction getter, JsNativeFunction setter) {
		JsPropertyIdRef namePropertyId;
		JsGetPropertyIdFromName_(name, &namePropertyId);

		JsValueRef propertyDesc;
		JsCreateObject_(&propertyDesc);

		JsValueRef get = NULL, set = NULL;
		if (getter != nullptr)
			JsCreateFunction_(getter, 0, &get);
		if (setter != nullptr)
			JsCreateFunction_(setter, 0, &set);

		JsValueRef jsTrue;
		JsGetTrueValue_(&jsTrue);
		JsValueRef jsFalse;
		JsGetFalseValue_(&jsFalse);

		if (getter != nullptr)
			addPropertyToObj(propertyDesc, L"get", get);
		if (setter != nullptr)
			addPropertyToObj(propertyDesc, L"set", set);
		addPropertyToObj(propertyDesc, L"enumerable", jsTrue);
		addPropertyToObj(propertyDesc, L"configurable", jsFalse);

		bool result;
		JsDefineProperty_(object, namePropertyId, propertyDesc, &result);
		return result;
	}

	void getProperty(JsValueRef obj, const wchar_t* str, JsValueRef* prop) {
		JsPropertyIdRef namePropertyId;
		JsGetPropertyIdFromName_(str, &namePropertyId);
		JsGetProperty_(obj, namePropertyId, prop);
	}

	bool isNullOrUndefined(JsValueRef ref) {
		JsValueType type = JsUndefined;
		JsGetValueType_(ref, &type);
		return type == JsUndefined || type == JsNull;
	}

	std::wstring valueToString(JsValueRef value) {
		if (value == JS_INVALID_REFERENCE)
			return L"INVALID_REFERENCE";
		JsValueRef resultJSString;
		auto err = JsConvertValueToString_(value, &resultJSString);
		if (err == JsNoError) {
			const wchar_t* resultWC;
			size_t stringLength;
			err = JsStringToPointer_(resultJSString, &resultWC, &stringLength);

			if (err == JsNoError)
				return std::wstring(resultWC, stringLength);
			else
				return std::wstring(L"error1#") + std::to_wstring(err);
		} else
			return std::wstring(L"error2#") + std::to_wstring(err);
	}

	JsValueRef arrayGet(JsValueRef arr, int index) {
		JsValueRef indexNum, result;
		JsIntToNumber_(index, &indexNum);
		JsGetIndexedProperty_(arr, indexNum, &result);
		return result;
	}

	void arraySet(JsValueRef arr, int index, JsValueRef value) {
		JsValueRef indexNum;
		JsIntToNumber_(index, &indexNum);
		JsSetIndexedProperty_(arr, indexNum, value);
	}
};