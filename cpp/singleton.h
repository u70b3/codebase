class Singleton {
private:
	Singleton() { };
	~Singleton() { };
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
public:
	static Singleton& getInstance() // 返回引用
        {
		static Singleton instance; // 静态局部变量
		return instance;
	}
};
