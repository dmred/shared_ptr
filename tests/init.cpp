#include <shared_ptr.cpp>
#include <catch.hpp>
#include <iostream>

SCENARIO("count get", "[count_and_get]"){
	  shared_ptr<size_t> s;
	  REQUIRE(s.count()==0);
    REQUIRE(s.get()==nullptr);
}

SCENARIO("get for shared inotoalize", "[get_share]"){
	  shared<size_t> s(new size_t(7));
	  REQUIRE(s.get()==nullptr);
}

SCENARIO("Initialize shared", "[InShGet]") {
	size_t * ptr = new size_t[10];
	shared_ptr<size_t> s(ptr);
	REQUIRE(ptr == s.get());
}

SCENARIO("check_UseCount", "[check_UseCount]"){
	  shared_ptr<int> s1(new int(7));
	  shared_ptr<int> s2 = std::move(sp1);
	  REQUIRE(*s2 == 7);
	  REQUIRE(s2.use_count() == 1);
}

SCENARIO("prisv1", "[prisv1]"){
	  shared_ptr<int> s1(new int(7));
	  shared_ptr<int> s2; 
	  s2 = s1;
	  REQUIRE(*s2 == 7);
	  REQUIRE(s2.use_count() == 2);
}

SCENARIO("prisv2", "[prisv2]"){
	  shared_ptr<int> s1(new int(7));
	  shared_ptr<int> s2;
	  sp2=std::move(s1);
	  REQUIRE(*s2 == 7);
	  REQUIRE(s2.use_count() == 1);
}

SCENARIO("swap", "[swap]"){
	  shared_ptr<int> s1(new int(7));
	  shared_ptr<int> s2(new int(77));
	  s1.swap(s2);
	  REQUIRE(*s1 == 77);
	  REQUIRE(*s2 == 7);
}

SCENARIO("reset", "[reset]"){
	  shared_ptr<int> s(new int(7));
	  s.reset(nullptr);
	  REQUIRE(!s.get());
}

SCENARIO("get", "[get]"){
	  shared<int> s(new int(7));
	  REQUIRE(*s.get() == 7);
}

/*SCENARIO("op_->", "op_->"){
	class tmp{
	public:
		int t;
		tmp(int x) : t(x){}
	};
	tmp a(7);
	shared_ptr<tmp> sptr1=make_shared<tmp>(std::move(a));
	REQUIRE(sptr1->a1 == 7);
}

SCENARIO("op_*", "[op_*]"){
	  shared_ptr<int> sp(new int(7));
	  REQUIRE(*sp == 7);
}
*/

SCENARIO("countref", "[countref]"){
	  shared_ptr<int> s1(new int(7));
	  shared_ptr<int> s2 = s1;
	  shared_ptr<int> s3;
	  s3 = s2;
	  REQUIRE(s2.use_count() == 3);
}

SCENARIO("make_shared", "[make_shared]"){
	int a = 7;
	shared<int> s = make_shared<int>(std::move(a));
	REQUIRE(*s==7);
	}

SCENARIO("test", "[test]"){
	shared_ptr<int> sptr1;
	shared_ptr<int> sptr2{ sptr1 };
	REQUIRE(sptr2.use_count()==0);
}
