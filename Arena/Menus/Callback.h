#pragma once
#ifndef CALLBACK_H
#define CALLBACK_H

//template < class Class, typename ReturnType, typename Parameter >
//class CallBack
//{
//public:
//	typedef ReturnType (Class::*Method)(Parameter);
//
//	CallBack(const Class * const instance, const Method &method) : m_Instance(instance), m_Method(method)
//	{
//	}
//
//	ReturnType operator()(Parameter param)
//	{
//		return (this->m_Instance->*this->m_Method)(param);
//	}
//
//	ReturnType execute(Parameter param)
//	{
//		return operator()(param);
//	}
//
//private:
//	const Class * const m_Instance;
//	const Method &m_Method;
//};

//
//template < class Class, typename ReturnType, typename Parameter >
//class CallBack
//{
//public:
//	typedef ReturnType(Class::*Method)(Parameter);
//
//	CallBack(Class *instance, Method method) : m_Instance(instance), m_Method(method)
//	{
//	}
//
//	ReturnType operator()(Parameter param)
//	{
//		return (this->m_Instance->*this->m_Method)(param);
//	}
//
//	ReturnType execute(Parameter param)
//	{
//		return operator()(param);
//	}
//
//private:
//	Class *m_Instance;
//	Method m_Method;
//};

#endif