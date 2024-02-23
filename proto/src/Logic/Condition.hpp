#pragma once

class Condition
{
private:
	void* args;

	bool (*func)(void* args);

	void Init()
	{
		args = nullptr;
		func = nullptr;
	}

public:
	Condition(bool (*func)(void* args), void* args)
	{
		Init();

		if(func)
		{
			this->func = func;
		}

		this->args = args;
	}

	Condition(bool (*func)(void* args))
	{
		Init();

		if(func)
		{
			this->func = func;
		}
	}

	Condition()
	{
		Init();
	}

	void Set(bool (*func)(void* args), void* args)
	{
		this->func = func;
		this->args = args;
	}

	void Set(bool (*func)(void* args))
	{
		this->func = func;
	}

	bool IsSet()
	{
		return (func != nullptr);
	}

	//make user choose between explicit args/no args execution
	int ExecuteNoArgs()
	{
		if(func)
		{
			return func(nullptr);
		}

		return -1;
	}

	int ExecuteWithArgs()
	{
		if(func && args)
		{
			return func(args);
		}

		return -1;
	}

};