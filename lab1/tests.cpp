#include <gtest/gtest.h>
#include "../CircularBuffer.h"
#include <iostream>

TEST(CircularBuffer, capacityConstructor) {
    CircularBuffer cb(10);
    
    EXPECT_EQ(0, cb.size());
    EXPECT_EQ(10, cb.capacity());
	EXPECT_TRUE(cb.empty());
	EXPECT_FALSE(cb.full());
}	

TEST(CircularBuffer, defaultConstructor) {
	CircularBuffer cb;
	
	EXPECT_EQ(0, cb.size());
	EXPECT_EQ(0, cb.capacity());
	EXPECT_TRUE(cb.empty());
	EXPECT_TRUE(cb.full());
}

TEST(CircularBuffer, capacityElemConstructor) {
	CircularBuffer cb(10, 8);
	
	EXPECT_EQ(10, cb.size());
    EXPECT_EQ(10, cb.capacity());
	EXPECT_FALSE(cb.empty());
	EXPECT_TRUE(cb.full());
	for (int i = 0; i != 10; ++i) {
		EXPECT_EQ(8, cb[i]);
	}
}

TEST(CircularBuffer, copyConstructor) {
	CircularBuffer a(10, 8);
	
	CircularBuffer b(a);
	
	EXPECT_EQ(10, b.size());
	for (int i = 0; i != 10; ++i) {
		EXPECT_EQ(a[i], b[i]);
	}
}

TEST(CircularBuffer, push_back) {
	CircularBuffer cb(10);
	
	for (int i = 0; i != 10; ++i) {
		cb.push_back(i);
	}
	
	EXPECT_TRUE(cb.full());
	for (int i = 0; i != 10; ++i) {
		EXPECT_EQ(cb[i], i);
	}
}

TEST(CircularBuffer, push_front) {
	CircularBuffer cb(5);
	
	for (int i = 0; i != 5; ++i) {
		cb.push_front(i);
	}
	
	EXPECT_TRUE(cb.full());
	EXPECT_EQ(cb[0], 4);
	EXPECT_EQ(cb[1], 3);
	EXPECT_EQ(cb[2], 2);
	EXPECT_EQ(cb[3], 1);
	EXPECT_EQ(cb[4], 0);
}

TEST(CircularBuffer, at) {
	CircularBuffer cb(10,1);
	
	for(int i = 0; i < 10; ++i) {
		cb.at(i) = 2;
	}
	
	EXPECT_THROW(cb.at(-1), std::out_of_range);
	EXPECT_THROW(cb.at(999), std::out_of_range);
	for(int i = 0; i < 10; ++i) {
		EXPECT_EQ(2, cb.at(i));
	}
}

TEST(CircularBuffer, atConst) {
	const CircularBuffer cb(10,1);
	
	EXPECT_THROW(cb.at(-1), std::out_of_range);
	EXPECT_THROW(cb.at(999), std::out_of_range);
	for(int i = 0; i < 10; ++i) {
		EXPECT_EQ(1, cb.at(i));
	}
}

TEST(CircularBuffer, assigmentOperator) {
	CircularBuffer cb(10, 1);
	
	for(int i = 0; i < 10; ++i) {
		cb[i] = 2;
	}
	
	for(int i = 0; i < 10; ++i) {
		EXPECT_EQ(2, cb[i]);
	}	
}

TEST(CircularBuffer, assigmentOperatorConst) {
	const CircularBuffer cb(10, 1);
	
	for(int i = 0; i < 10; ++i) {
		EXPECT_EQ(1, cb[i]);
	}
}

TEST(CircularBuffer, frontConstAndBackConst) {
	const CircularBuffer cb(3,1);
	
	EXPECT_EQ(1, cb.front());
	EXPECT_EQ(1, cb.back());
}

TEST(CircularBuffer, front) {
	CircularBuffer cb(5);
	cb.push_back(1);
	cb.push_back(2);
	cb.push_back(3);
	cb.push_back(4);
	cb.push_back(5);
	cb.push_back(6);
	cb.push_back(7);
	cb.push_back(8);
	cb.push_back(9);
	
	EXPECT_EQ(5, cb.front()); 
	
	cb.push_front(11);
	
	EXPECT_EQ(11, cb.front());
}

TEST(CircularBuffer, back) {
	CircularBuffer cb(5, 0);
	cb.push_back(1);
	
	EXPECT_EQ(1, cb.back());
	
	cb.push_front(2);
	cb.push_front(3);
	cb.push_front(4);
	cb.push_front(5);
	cb.push_front(6);
	cb.push_front(7);
	
	EXPECT_EQ(3, cb.back());
}

TEST(CircularBuffer, Pop) {
	CircularBuffer cb(5);	
	for (int i = 0; i < 5; ++i) {
		cb.push_back(i + 1);
	}

	for (int i = 0; i < 4; ++i) {
		cb.pop_back();
	}
	
	EXPECT_EQ(cb[0], 1);
	
	cb.pop_front();
	
	EXPECT_TRUE(cb.empty());
}

TEST(CircularBuffer, reserve) {
	CircularBuffer cb(10);
	cb.push_front(1);
	
	EXPECT_EQ(9, cb.reserve());
}

TEST(CircularBuffer, setCapacity) {
	CircularBuffer cb(10);
	for (int i = 0; i < 10; ++i) {
		cb.push_back(i);
	}
	
	cb.set_capacity(12);
	
	EXPECT_EQ(12, cb.capacity());
	
	cb.set_capacity(5);
	
	EXPECT_EQ(5, cb.capacity());
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(cb[i], i);
	}	
	
	cb.set_capacity(12);
	for (int i = 0; i < 20; ++i) {
		cb.push_front(i);
	}
	
	for (int i = 0; i < 12; ++i) {
		EXPECT_EQ(19 - i, cb[i]);
	}	
}

TEST(CircularBuffer, clear) {
	CircularBuffer cb(7,45);
	
	cb.clear();
	
	EXPECT_TRUE(cb.empty());
	EXPECT_EQ(0, cb.size());
}

TEST(CircularBuffer, Swap){
	CircularBuffer a(10,3);
	CircularBuffer b(9,4);
	
	a.swap(b);
	
	for(int i = 0; i != 10; ++i) {
		EXPECT_EQ(3, b[i]);
	}
	EXPECT_EQ(10, b.capacity());
	EXPECT_EQ(10, b.size());
	for(int i = 0; i != 9; ++i) {
		EXPECT_EQ(4, a[i]);
	}
	EXPECT_EQ(9, a.capacity());
	EXPECT_EQ(9, a.size());
}

TEST(CircularBuffer, swapWithEmpty){
	CircularBuffer a;
	CircularBuffer b(9,4);
	
	a.swap(b);

	EXPECT_EQ(0, b.capacity());
	EXPECT_EQ(0, b.size());
	EXPECT_TRUE(b.empty());
	for(int i = 0; i != 9; ++i) {
		EXPECT_EQ(4, a[i]);
	}
	EXPECT_EQ(9, a.capacity());
	EXPECT_TRUE(a.full());
	EXPECT_EQ(9, a.size());
}

TEST(CircularBuffer, operatorAssigment) {
	CircularBuffer a(10, 2);
	
	CircularBuffer b = a;
	
	EXPECT_EQ(10, b.size());
	EXPECT_EQ(10, b.capacity());
	EXPECT_TRUE(a == b);
}

TEST(CircularBuffer, isLinearized) {
	CircularBuffer a(3, 1);
	
	EXPECT_TRUE(a.is_linearized());
	
	a.push_front(2);
	a.push_front(2);
	a.push_front(2);
	
	EXPECT_TRUE(a.is_linearized());
	
	a.push_front(2);
	
	EXPECT_FALSE(a.is_linearized());
}

TEST(CircularBuffer, linearized) {
	CircularBuffer a(3);
	int* b;
	a.push_back(3);
	a.push_back(3);
	a.push_back(3);
	a.push_back(3);
	a.push_back(3);
	a[1] = 1;
	a[2] = 2;
	
	b = a.linearized();
	
	EXPECT_TRUE(a.is_linearized());
	EXPECT_EQ(b[0], a[0]);
	EXPECT_EQ(b[1], a[1]);
	EXPECT_EQ(b[2], a[2]);
	EXPECT_EQ(3, a[0]);
	EXPECT_EQ(1, a[1]);
	EXPECT_EQ(2, a[2]);		
}

TEST(CircularBuffer, rotateFull) {
	CircularBuffer a(4);
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	
	a.rotate(3);
	
	EXPECT_TRUE(a.is_linearized());
	EXPECT_EQ(4, a[0]);
	EXPECT_EQ(1, a[1]);
	EXPECT_EQ(2, a[2]);
	EXPECT_EQ(3, a[3]);
}

TEST(CircularBuffer, rotate1) {
	CircularBuffer a(4);
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	
	a.rotate(2);
	
	EXPECT_TRUE(a.is_linearized());
	EXPECT_EQ(3, a[0]);
	EXPECT_EQ(1, a[1]);
	EXPECT_EQ(2, a[2]);
}

TEST(CircularBuffer, rotate2) {
	CircularBuffer a(3);
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	
	a.rotate(2);
	
	EXPECT_EQ(4, a[0]);
}

TEST(CircularBuffer, insertFull) {
	CircularBuffer cb(5);
	cb.push_back(1);
	cb.push_back(2);
	cb.push_back(3);
	cb.push_back(4);
	cb.push_back(5);
	
	cb.insert(3, 9);
	
	EXPECT_EQ(9, cb[3]);
	EXPECT_EQ(2, cb[0]);
	EXPECT_EQ(3, cb[1]);
	EXPECT_EQ(4, cb[2]);
	EXPECT_EQ(5, cb[4]);
}

TEST(CircularBuffer, insertNotFull) {
	CircularBuffer cb(5);
	cb.push_back(1);
	cb.push_back(2);
	cb.push_back(3);

	cb.insert(2, 7);
	
	EXPECT_EQ(7, cb[2]);
	EXPECT_EQ(1, cb[0]);
	EXPECT_EQ(2, cb[1]);
	EXPECT_EQ(3, cb[3]);
}

TEST(CircularBuffer, insert) {
	CircularBuffer cb(6);
	cb.push_back(1);
	cb.push_back(2);
	cb.push_back(3);
	cb.push_back(4);
	
	cb.insert(5, 9);
	
	EXPECT_EQ(9, cb[4]);
	EXPECT_EQ(1, cb[0]);
	EXPECT_EQ(2, cb[1]);
	EXPECT_EQ(3, cb[2]);
	EXPECT_EQ(4, cb[3]);
}

TEST(CircularBuffer, erase) {
	CircularBuffer cb(5);	
	cb.push_back(1);
	cb.push_back(2);
	cb.push_back(3);
	cb.push_back(4);
	cb.push_back(5);
	
	cb.erase(1,4);
	
	EXPECT_EQ(1, cb[0]);
	EXPECT_EQ(5, cb[1]);
}

TEST(CircularBuffer, operatorEqual) {
	CircularBuffer a(2,3);
	CircularBuffer b(2,3);
	
	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
}

TEST(CircularBuffer, operatorNotEqual) {
	CircularBuffer a(3, 3);
	CircularBuffer b(5, 3);
	
	EXPECT_TRUE(a != b);
	EXPECT_FALSE(a == b);
}

TEST(CircularBuffer, operatorEqualDiferentElements) {
	CircularBuffer a(3, 1);
	CircularBuffer b(3, 0);
	
	EXPECT_FALSE(a == b);
}

TEST(CircularBuffer, resizeBuffer) {
	CircularBuffer a(10,1);
	
	a.resize(5);
	
	EXPECT_EQ(5, a.size());
	for(int i = 0; i < a.size(); ++i) {
		EXPECT_EQ(1, a[i]);
	}
	
	a.resize(11,1);
	for(int i = 0; i < a.size(); ++i) {
		EXPECT_EQ(1, a[i]);
	}
}

TEST(CircularBuffer, operatorAssigmment) {
	CircularBuffer a1(10,1);
	CircularBuffer a2;
	a2 = a1;
	EXPECT_TRUE(a2 == a1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
