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
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::GetStyle().WindowBorderSize = 0.0f;
}


template<>
void GUIInput<int>::SpecificRenderingTasks()
{
	int holdOldValue = value;
	ImGui::InputInt(label.c_str(), reinterpret_cast<int*>(&value));
	(holdOldValue != value) ? this->valueChangeCallback(value) : NULL;
}
template<>
void GUIInput<float>::SpecificRenderingTasks()
{
	float holdOldValue = value;
	ImGui::InputFloat(label.c_str(), reinterpret_cast<float*>(&value));
	(holdOldValue != value) ? this->valueChangeCallback(value) : NULL;
}
template<>
void GUIInput<double>::SpecificRenderingTasks()
{
	double holdOldValue = value;
	ImGui::InputDouble(label.c_str(), reinterpret_cast<double*>(&value));
	(holdOldValue != value) ? this->valueChangeCallback(value) : NULL;
}
template<>
void GUIInput<string>::SpecificRenderingTasks()
{
	string holdOldValue = value;
	// In 'this->maxLength + 1', '+ 1' will be '\0' character at the end 
	char* stringBuffer = new char[this->maxLength + 1];
	strcpy(stringBuffer, value.c_str());
	ImGui::InputText(label.c_str(), stringBuffer, this->maxLength + 1);
	value = stringBuffer;
	(holdOldValue != value) ? this->valueChangeCallback(value) : NULL;
}


template class GUIInput<string>;
template class GUIInput<int>;
template class GUIInput<float>;
template class GUIInput<double>;

