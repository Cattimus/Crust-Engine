#pragma once

class Action
{
private:
	void* args;

	void (*func)(void* args);

	void Init()
	{
		args = nullptr;
		func = nullptr;
	}

public:
	Action(void (*func)(void* args), void* args)
	{
		Init();

		if(func)
		{
			this->func = func;
		}

		this->args = args;
	}

	Action(void (*func)(void* args))
	{
		Init();

		if(func)
		{
			this->func = func;
		}
	}

	Action()
	{
		Init();
	}

	void Set(void (*func)(void* args), void* args)
	{
		this->func = func;
		this->args = args;
	}

	void Set(void (*func)(void* args))
	{
		this->func = func;
	}

	bool IsSet()
	{
		return (func != nullptr);
	}

	//Make the user choose between explicit args/no args execution
	void ExecuteNoArgs()
	{
		if(func)
		{
			func(nullptr);
		}
	}

	void ExecuteWithArgs()
	{
		if(func && args)
		{
			func(args);
		}
	}

};