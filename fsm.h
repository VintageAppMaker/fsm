/*
       제목  : 상태관리자-FSM
       목적  : 프로그램의 한정된 흐름을 규칙적으로 제어한다.
       작성자: 박성완
       작성일: 2005.04.20
   
   
       참고  : 1) 상태와 이벤트로 분기점을 가진다.
              2) Handler 테이블로 관리할 수 있다.
              3) 상태전이에 대한 메소드를 제공한다. 
              4) 상태는 내부에서 제어한다. 이벤트는 외부 입력항목이다.
    
      수정일: 2007.08.02
           1) 좀더 간략하게 처리 하기 위해 TABLE 삭제 
  
      수정일: 2017.08.22 <- 10년만!!
           1) VC6.0 소스를 C++ 11 및 g++에 맞게 수정  
 
             
 */
 
 #ifndef __PSW_SNAKE_CFSM_BASE__
 #define __PSW_SNAKE_CFSM_BASE__
 
 // 매크로 정의부
 #define STATE( a ) SetAction( static_cast<CFSM::Action>( a )  );
 #define BEGIN_EVT_MAP( e ) switch(e.EVT){ 
 #define END_EVT_MAP }
   
 #define CNT_EVT return CFSM::CONTINUE;
 #define END_EVT break;
   
 #define ONEVENT( a ) case a:
 #define PASS_EVT( a )  STATE( a ) CNT_EVT;
 
 // 이벤트와 매개변수
 // 처리 클래스 
 class CFSM_EVT
 {
 public:
     unsigned EVT;
     long     pParam;
 };
  
 // 한정상태기계(Finate State Machine)
 // BASE 클래스 
 class CFSM
 {
 public:
     typedef int (CFSM::*Action)(CFSM_EVT);
     CFSM(){StateHandler = &CFSM::doNothing; }
 
     enum state{
         COMPLETE = 0,  // 메시지 처리 완료
         CONTINUE       // 상태변화 메시지, 처리 진행 한번더..
     };
  
     // >>외부 이벤트 처리 
     // 설정된 이벤트와 상태값을 X,Y로
     // 핸들러테이블의 함수를 호출한다.
     void DoEvent(CFSM_EVT evt)
     {
         int nRst = 1;
         while (nRst){
             nRst = (this->*StateHandler)(evt);
         }
     }
 
     // 아무것도 안하는 함수는 어디서나 필요하다.
     int doNothing(CFSM_EVT e) { return COMPLETE;}
  
 protected:
     // 상태를 전이한다.
     inline void SetAction(Action a)
     {
         StateHandler = a;
     }
 
 private:
     Action   StateHandler;
 };
 #endif
 
