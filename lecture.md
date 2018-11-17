## **cudaDeviceSynchronize()**; // 연산 결과를 동기화 매우 중요

gpu함수
```
// gloval 아니다!!!
__global__ void helloGPU(){
    printf("hi gpu");
}

int main()
{
    helloGPU<<<1, 1>>>();   // gpu로 함수 호출
    cudaDeviceSynchronize();        // 결과 싱크로
}
```

# <<<num1, num2>>>에 관하여
num1은 블록. num2는 블록안에 들어있는 쓰레드

# cuda에서 기본적으로 제공해주는 변수
Cuda는 executing thread, block, grid라는 변수를 제공해준다.
- gridDim.x = grid안에 있는 블럭의 수 
    + grid는 블록을 모아놓은 단위
    + 인덱싱이 가능하다. 
- blockIdx.x - grid 안에 block index
- blockDim.x - block 안에 thread 갯수
- threadIdx.x - block 안에 쓰레드 index

이 인덱스들은 0부터 시작한다. 
func<<<256, 1024>>>(); 라고 지정해주면
blockIdx.x = 255.
threadIdx.x = 1023이다.

# for문을 cuda kernal에...
8개의 작업이 있으면
4개의 쓰레드를 갖고있는 2개의 블럭으로 생각해보자.
threadIdx.x + blockIdx.x * blockDim.x

# cuda에서 동적할당
- cudaMallocManaged(type *p, size);
- cudaFree(a);

**CPU에서 동적할당한(malloc) 메모리는 GPU에서 못쓰지만
GPU에서 동적할당한(cudaMallockManaged) 메모리는 CPU에서 쓸 수 있다.**

# DATA 갯수를 맞춰주자
data가 5개가 있고 block은 2개, thread가 4개씩 있으면
8개의 data를 처리할 수 있다.
data[0]~data[4]까지는 처리할 수 있으나 남은 data[5]~data[7]는 없기 때문에 쓰레드가 짝이 안맞는다. => 에러발생
> solution : if문을 활용하여 예외처리 해준다.

* tip : 보통 블럭당 256개의 쓰레드를 사용. 그 이상은 성능상 별로 ..
block 갯수 계산
* tip : block당 최대 쓰레드가 보통 1024개임. /* 확인 필요 */
```
__global__ some_kernel(int N)
{
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if(idx < N) { // check 
        // do something 
    }
}

int N = 100000;
size_t threads_per_block = 256;
size_t number_of_blokcs = (N + thread_per_block -1) / thread_per_block;

some_kernel<<<number_of_blocks, threads_per_block>>>(N);

```

# grid-stride loop
data가 grid보다 많은 경우
block - 2
thread - 4일때
9번째 data 접근은 gridDim.x * blockDim.x로 접근.
여기서 gridDim.x = 2, blockDim.x = 4이다.

처리해야 할 data가 32개일경우
1. 0번째 블록의 0번째 쓰레드가 처리하는 데이터들은
0,8,16,24번째 데이터들을 처리한다.

2. 0번째 블록의 1번째 쓰레드가 처리하는 데이터들은
1,9,17,25번째 데이터들을 처리한다.

3. 0번째 블록의 2번째 쓰레드가 처리하는 데이터들은
2,10,18,25번째 데이터들을 처리한다.

4. 0번째 블록의 3번째 쓰레드가 처리하는 데이터들은
3,11,19,27번째 데이터들을 처리한다.

5. 1번째 블록의 0번째 쓰레드가 처리하는 데이터들은
4,12,20,28번째 데이터들을 처리한다.

// 중략

5. 1번째 블록의 4번째 쓰레드가 처리하는 데이터들은
7,15,23,31번째 데이터들을 처리한다.


하나씩 해보자.
data1 = blockDim.x * blockIdx + threadIdx.x + gridDim.x * blockDim.x;
// 4 * 0 + 0 + 2 * 4 = 8
> tip - gridDim.x에서 Dim은 dimension으로 차원이라는 뜻이다.


# cuda error handle
```
cudaError_t err; 
err = cudaMallocManaged(&a,N);

if(err != cudaSuccess)
{
    printf("Error: %s\n", cudaGetErrorString(err)); 
}
```

cudaSuccess와 cudaGetErrorString함수는 cuda에서 자체적으로 지원해준다.


# cuda가 추구하는 APOD
* A: Assess
* P: Parallelize
* O: Optimize
* D: Deploy

# nprof
NVIDIA Command Line Profiler
성능체크하는데 사용함
nvprof ./실행파일
# streaming multiprocessors == SMs
gpu는 Sms라는 프로세스 유닛이 있음.
커널이 실행되는 동안에 블록의 스레드는 SMs를 실행하기 위해 줌 
권장되는 방법. 익숙해져야함

```
int deviceId;
cudaDeviceProp props;

cudaGetDevice(&deviceId);
cudaGetDeviceProperties(&props, deviceId); 
```


# Unified Memory(UM)
UM은 CPU와 GPU에 없는 제3의 메모리다. page fault 발생
Host(CPU) -> Device(GPU)로 스위칭할때 시간이 걸림.
1. CPU단에서 cudaMallocManaged()를 호출하고 init()함수를 호출하면 UM을 CPU가 사용할 수 있도록 슥 갖고온다.
2. kernel 함수를 호출하면 GPU가 슥 CPU가 가져간걸 갖고간다.
3. GPU작업이 끝난걸 CPU가 슥 가져간다.

**cudaMemPreFetchAsync(data, size, dest) : 미리 UM dest가 가져간다고 callee한테 알려준다. => page fault시간 줄임**
- dest: deviceId, cudaCpuDeviceId (cuda 내부적으로 제공해주는 변수)
- compile option: prefetch-to-cpu or prefetch-to-gpu    

처음 시작할때 gpu->cpu가 cpu->gpu보다 속도가 좋다.
# Concurrent cuda streams
stream은 instructions(기본 단위)의 연속이다. 
그리고 cuda는 default stream을 갖는다.

우리의 kernel 함수들은 default stream에서 작동한다. 
이 kernel들은 차례대로 실행된다.

#### 욕심 좀 부려보자.
스트림을 더 만들 수 있고 kernel을 스트림을 따로 지정해줄 수 있으며 비동기로 올릴 수 있다.
예를들어 스트림1과 스트림2를 만들었다고 가정하자. 

__flow__ ---------------------------------->
+ stream1 : kernel1 kernel3
+ stream2 :    kerenl2   kenerl4
+ default : 

**default stream은 특별하여 작업이 있을 경우 다른 스트림들은 작업중이던 kernel을 block하고 작업이 끝나면 다시 사용 할 수 있다.**

```
cudaStream_t stream;            // cuda stream type
cudaStreamCreate(&stream);       // stream 등록

// 네번째 인자로 스트림. 세번째는 shared_memory. 안쓰니 0 
someKernel<<<number_of_blocks, threads_per_block, 0, stream>>>(); 

cudaStreamDestroy(stream);        // stream 삭제
```

Q: 아까 예제에서 kernel을 스트림에 올리고 cudaStreamDestroy()를 호출하는데 그러면 커널이 끝날때까지 스트림이 파괴되지 않는것을 보장하나요?
A: CPU일 경우 그런 걱정이 되겠지만 GPU는 한번에 다 올린 후 처리하기때문에 그렇게 긴 작업이 걸릴 경우는 드물며 내부적으로 **보장해 줄 것이다.**

# 메모리 관리 메뉴얼 예제
실시간에서 유용한 코드
```
int *host_a, *device_a;
cudaMalloc(&device_a, size); // device_a = gpu
cudaMallocHost(&host_a, size); // host_a = cpu, page-locked, or pinned

initializeOnHost(host_a, N);  

// 즉석으로 빠르게 카피한다.
cudaMemcpy(device_a, host_a, size, cudaMemcpyHostToDevice);

kernel<<<blocks, threads, 0, someStream>>>(device_a, N);

verifyOnHost(host_a, N); // migration보다 속도가 엄청 빠름
cudaFree(device_a);
cudaFreeHost(host_a);
```