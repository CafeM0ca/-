# 2018/12/15 모두콘

## 쫄지말자 딥러닝 
함수는 system or filter라고 부르기도 함

* 몬테칼로 시뮬레이션
구술을 던져서 함수를 미중

+ supervised learning
    - 정답이 주어진다.
    - 비교적 문제풀이가 쉽다.
    - 대부분의 딥러닝 모델은 supervised learning이라고 생각하면 된다.
+ unsupervised learning
    - 풀 수가 없는 어려운문제..
    - 방정식이 하나고 미지수가 두개면 풀 수 있을까?
    - 부정방정식이 대표적이다.
    - 특수한 경우에 특수한 조건이 있을 때 풀 수 있다. 
+ reinforced learning
    - 2020년 모두콘에..


#### 뉴런과 인공뉴런
뉴런이 값들을 모아서 필요한 것들만 모아 전송한다.
이를 인공뉴런으로 바꾸면 input들을 weight를 주어서 일정 값 이상이 되면 통과시킨다.

+ Nonlinear activation function
    - 일정 값 이상이면 통과시킴

뉴런과 뉴런을 이은것 **뉴런 네트워크**
뉴런에서 뉴런으로 갈 때마다 nonlinear function이 하나씩 들어간다.
그럼 layer가 2개면 nonleinear function이 두개가 들어간다.
이런식으로 layer가 많이 쌓이면 복잡한 인공지능이 완성된다.

layer를 많이 쌓는건 2가지 문제가 있다..
+ overfitting
    - 연습문제는 엄청 잘 푸는데 시험만 보면 망함.
    - 너무 복잡한 함수로 만들면 오히려 성능이 떨어짐. 
    - 해결 방안 
        * dropout: 랜덤하게 뉴런을 끊음으로써 모델을 단순하게 만든다.
+ vanishing gradient
    - 학습되는 양 = 미분값 * 출력값
    - 대부분의 영역에서 미분값이 0에 가까움
    - 출력의 최대값이 1이다. 출력값이 0.5라고 했을 때 4개의 레이어만 지나도 1/16

#### ReLu
미분값이 1. 출력값은 제한 없음

#### Convolutional Nenural Network(CNN)
+ Convolution (operator)?
    - 사칙연산보다 조금 더 복잡한 연산정도.
    - [2 3] * [1 1]  = [253]
    - 세로축에서 보면 겹치는 부분이 없다. 따라서 오른쪽으로 쉬프트 하고 세로로 더한다.
    ```
            2 3
        1 1         // 겹치는 부분이 없으니 오른쪽으로 한칸 쉬프트

            2 3
          1 1       // 2와 1이 겹치고 3과 2가 겹친다. 세로로 더해주자.
        ----------
            2 

            2 3
            1 1      // 2와 1이 겹치고 3과 2가 겹친다. 세로로 더해주자.
        ----------
            2 5


    ```


## 깊은 코끼리를 냉장고에 넣기
**직접 짜봐라. 프레임워크에 종속되지 말고.**

# 쿠쿠다스 CUDA
최신 드라이브 버전 업데이트 해야한다.
도커 쓰면 이런 문제 쉽게 해결 가능

+ AWS Deep Learning AMI는 기본으로 다 설정되어 있음     => 이게 남.
+ NCLOUD gpu server에도 nvcc 컴파일러가 포함되어 있다.

+ 보통 GPU 하나당 한시간에 천원정도 듬..

### 리눅스에서 컴파일
+ nvcc filename.cu -o 실행파일


### 책 추천
예제로 배우는 cuda 프로그래밍
+ source code
    - https://github.com/lishengzhe/cuda_by_example_vs2017


### 메모리 종류
* private local memory
    - Thread 내부에서 생성되고 Thread 사이에 공유할 수 없음
* shared memory
    - Thread에서 생성되고 같은 Block에서 공유 할 수 있음
* Global memory
    - 디바이스 전체에서 접근 가능. 디폴트임
* constant memory
    - Thread 내부에서 읽기 전용.
    - 매우 작음
* Texture memory
    - 디바이스 전체에서 접근 가능, text2D 함수로 접근

### Dot Product
두 백터를 곱하고 더함
* (x1, x2, x3, x4) * (y1, y2, y3, y4) = x1y1 + x2y2 + x3y3 + x4+y4


* 병행 => 멀티쓰레드
* 병렬 => cuda


* \_\_device\_\_
    + 커널에서 호출 device에서 실행
* \_\_host\_\_
    + 호스트에서 호출하고 호스트 실행

GPU에서는 recursion이 불가능하다.

### Multi-core CPU : OpenMP

