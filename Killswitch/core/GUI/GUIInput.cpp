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
GUIInput<VALUE_TYPE>::GUIInput(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, string label, VALUE_TYPE value, int maxLength)
	: GUIWindow(nameID, guiWindowID, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, GUIWindowType::INPUT)
{
	this->label = label;
	this->value = value;
	this->maxLength = maxLength;
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

template<>
void GUIInput<int>::SpecificRenderingTasks()
{
	ImGui::InputInt(label.c_str(), reinterpret_cast<int*>(&value));
	cout << "INT TEXT IS: " << value << endl;
}
template<>
void GUIInput<float>::SpecificRenderingTasks()
{
	ImGui::InputFloat(label.c_str(), reinterpret_cast<float*>(&value));
	cout << "INT TEXT IS: " << value << endl;
}
template<>
void GUIInput<double>::SpecificRenderingTasks()
{
	ImGui::InputDouble(label.c_str(), reinterpret_cast<double*>(&value));
	cout << "INT TEXT IS: " << value << endl;
}
template<>
void GUIInput<string>::SpecificRenderingTasks()
{
	// In 'this->maxLength + 1', '+ 1' will be '\0' character at the end 
	char* stringBuffer = new char[this->maxLength+1];
	strcpy(stringBuffer, value.c_str());
	ImGui::InputText(label.c_str(), stringBuffer, this->maxLength+1);
	value = stringBuffer;
}


template class GUIInput<string>;
template class GUIInput<int>;
template class GUIInput<float>;
template class GUIInput<double>;

