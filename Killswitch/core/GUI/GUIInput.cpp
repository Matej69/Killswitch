#include "GUIInput.h"


template<class VALUE_TYPE>
GUIInput<VALUE_TYPE>::GUIInput()
{
	/*
	this->label = label;
	this->value = value;

	string valueType = typeid(VALUE_TYPE).name();
	if (valueType == "int")
		inputType = InputType::INT;
	else if (valueType == "float")
		inputType = InputType::FLOAT;
	else if (valueType == "double")
		inputType = InputType::DOUBLE;
	else
		inputType = InputType::STRING;
	*/
}

template<class VALUE_TYPE>
GUIInput<VALUE_TYPE>::~GUIInput()
{
}



template<class VALUE_TYPE>
GUIInput<VALUE_TYPE>::GUIInput(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, string label, VALUE_TYPE value)
	: GUIWindow(nameID, guiWindowID, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, GUIWindowType::INPUT)
{
	this->label = label;
	this->value = value;
	string valueType = typeid(VALUE_TYPE).name();
	if (valueType == "int")
		inputType = InputType::INT;
	else if (valueType == "float")
		inputType = InputType::FLOAT;
	else if (valueType == "double")
		inputType = InputType::DOUBLE;
	else
		inputType = InputType::STRING;
}

template<class VALUE_TYPE>
void GUIInput<VALUE_TYPE>::SpecificPreRenderingTasks()
{
	ImGui::SetNextWindowBgAlpha(0.0f);
	ImGui::GetStyle().WindowBorderSize = 0.0f;
}


/*
#"$("/&#$/&"#$/&"#/$&"#()$&"#)($&"#)($/&")#($&"#/$&##/&$)"#$/ FIND BULSHIT HERE "#(!"/#!"&$("$()"&=)!"&$=)(!"/$)(!"/$(/!"=)$(/"!)=($/!"
*/
static string* labelToBeLoaded;
static int inputCallback(ImGuiTextEditCallbackData* textEditCallbackData) {
	//labelToBeLoaded->assign(textEditCallbackData->Buf);
	//cout << *labelToBeLoaded;
	return 0;
}

#define TOSTRING(x) #x
template<class VALUE_TYPE>
void GUIInput<VALUE_TYPE>::SpecificRenderingTasks()
{
	//VALUE_TYPE* ptr = &value;
	if (inputType == InputType::INT)
		ImGui::InputInt(label.c_str(), reinterpret_cast<int*>(&value));
	else if (inputType == InputType::FLOAT)
		ImGui::InputFloat(label.c_str(), reinterpret_cast<float*>(&value));
	else if (inputType == InputType::DOUBLE)
		ImGui::InputDouble(label.c_str(), reinterpret_cast<double*>(&value));
	else
	{
		//int(GUIInput<VALUE_TYPE>::*ptr)(ImGuiTextEditCallbackData* textEditCallbackData) = &GUIInput::inputCallback;
		//ImGuiTextEditCallback callbackPtr = reinterpret_cast<ImGuiTextEditCallback>(ptr);
		//labelToBeLoaded = reinterpret_cast<string*>(&value);
		char* charPtrValue = TOSTRING(value).c_str();
		ImGui::InputText(label.c_str(), charPtrValue, 255, ImGuiInputTextFlags_CallbackAlways, inputCallback);
	}

	cout << "TEXT IS: " << value << endl;
}


template class GUIInput<string>;
template class GUIInput<int>;
template class GUIInput<float>;
template class GUIInput<double>;

