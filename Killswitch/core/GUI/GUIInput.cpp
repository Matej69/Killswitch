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
GUIInput<VALUE_TYPE>::GUIInput(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, string label, VALUE_TYPE value, void(*valueChangeCallback)(VALUE_TYPE), int max, int min)
	: GUIWindow(nameID, guiWindowID, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, GUIWindowType::INPUT)
{
	this->label = label;
	this->value = value;
	this->max = max;
	this->min = min;
	this->valueChangeCallback = valueChangeCallback;
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
	int oldValue = value;
	// disableing step on ImGui::InputInt disables +/- button option for changing value
	ImGui::InputInt(label.c_str(), reinterpret_cast<int*>(&value), NULL, NULL, 0);
	value = (oldValue != value && value > this->min && value < this->max) ? value : oldValue;
	(oldValue != value && value > this->min && value < this->max) ? this->valueChangeCallback(value) : NULL;
}
template<>
void GUIInput<float>::SpecificRenderingTasks()
{
	float oldValue = value;
	ImGui::InputFloat(label.c_str(), reinterpret_cast<float*>(&value));
	value = (oldValue != value && value > this->min && value < this->max) ? value : oldValue;
	(oldValue != value && value > this->min && value < this->max) ? this->valueChangeCallback(value) : NULL;
}
template<>
void GUIInput<double>::SpecificRenderingTasks()
{
	double oldValue = value;
	ImGui::InputDouble(label.c_str(), reinterpret_cast<double*>(&value));
	value = (oldValue != value && value > this->min && value < this->max) ? value : oldValue;
	(oldValue != value && value > this->min && value < this->max) ? this->valueChangeCallback(value) : NULL;
}
template<>
void GUIInput<string>::SpecificRenderingTasks()
{
	string holdOldValue = value;
	// In 'this->maxLength + 1', '+ 1' will be '\0' character at the end
	char* stringBuffer = new char[this->max + 1];
	strcpy(stringBuffer, value.c_str());
	ImGui::InputText(label.c_str(), stringBuffer, this->max + 1);
	value = stringBuffer;
	(holdOldValue != value) ? this->valueChangeCallback(value) : NULL;
}


template class GUIInput<string>;
template class GUIInput<int>;
template class GUIInput<float>;
template class GUIInput<double>;

