template<class T> struct Outer {
    template<class U> void member() {
        Member<U>::f();
    }   

private:
    template<class U, class = void> struct Member {
        static void f() {}
    };  
    template<class V> struct Member<int, V> {
        static void f() {}
    };  
};

int main(void){
	return 0;
}
