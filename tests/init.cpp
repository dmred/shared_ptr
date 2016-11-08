#include <shared_ptr.hpp>
#include <catch.hpp>
#include <iostream>

SCENARIO("count get", "[count_and_get]"){
	  shared_ptr<int> s;
	  REQUIRE(s.use_count()==0);
    REQUIRE(s.get()==nullptr);
}

SCENARIO("get for shared inotoalize", "[get_share]"){
	  shared_ptr<int> s(new int(1));
	  REQUIRE(s.get()!=nullptr);
}

SCENARIO("Initialize shared", "[InShGet]") {
	int * ptr = new int[10];
	shared_ptr<int> s(ptr);
	REQUIRE(ptr == s.get());
}

SCENARIO("check_UseCount", "[check_UseCount]"){
	  shared_ptr<int> s1(new int(1));
	  shared_ptr<int> s2 = std::move(s1);
	  REQUIRE(*s2 == 1);
	  REQUIRE(s2.use_count() == 1);
}

SCENARIO("prisv1", "[prisv1]"){
	  shared_ptr<int> s1(new int(1));
	  shared_ptr<int> s2; 
	  s2 = s1;
	  REQUIRE(*s2 == 1);
	  REQUIRE(s2.use_count() == 2);
}

SCENARIO("prisv2", "[prisv2]"){
	  shared_ptr<int> s1(new int(1));
	  shared_ptr<int> s2;
	  s2=std::move(s1);
	  REQUIRE(*s2 == 1);
	  REQUIRE(s2.use_count() == 1);
}

SCENARIO("swap", "[swap]"){
	  shared_ptr<int> s1(new int(1));
	  shared_ptr<int> s2(new int(2));
	  s1.swap(s2);
	  REQUIRE(*s1 == 2);
	  REQUIRE(*s2 == 1);
}

SCENARIO("reset", "[reset]"){
	  shared_ptr<int> s(new int(1));
	  s.reset(nullptr);
	  REQUIRE(!s.get());
}

SCENARIO("get", "[get]"){
	  shared_ptr<int> s(new int(1));
	  REQUIRE(*s.get() == 1);
}

SCENARIO("op_->", "op_->"){
	class MyClass
	{
	public:
		int MyInt;
		MyClass(int _MyInt) : MyInt(_MyInt){}
	};
	MyClass MyInt(123);
	shared_ptr<MyClass> s=make_shared<MyClass>(std::move(MyInt));
	REQUIRE(s->MyInt == 123);
}


SCENARIO("op_*", "[op_*]"){
	  class MyClass
	{
	public:
		int MyInt;
		MyClass(int _MyInt) : MyInt(_MyInt){}
	};
	MyClass MyInt(123);
	shared_ptr<MyClass> s=make_shared<MyClass>(std::move(MyInt));
	REQUIRE((*s).MyInt == 123);
	  //shared_ptr<int> s(new int(1));
	  //REQUIRE(*s == 1);
}


SCENARIO("countref", "[countref]"){
	  shared_ptr<int> s1(new int(1));
	  shared_ptr<int> s2 = s1;
	  shared_ptr<int> s3;
	  s3 = s2;
	  REQUIRE(s2.use_count() == 3);
}

SCENARIO("make_shared", "[make_shared]"){
	int a = 1;
	shared_ptr<int> s = make_shared<int>(std::move(a));
	REQUIRE(*s==1);
	}

SCENARIO("test", "[test]"){
	shared_ptr<int> sptr1;
	shared_ptr<int> sptr2{ sptr1 };
	REQUIRE(sptr2.use_count()==0);
}
