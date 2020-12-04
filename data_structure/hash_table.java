// 리니어, 뻐꾸기, 더블에 대해 구현
// 대학 외주

import java.util.Random;
import java.util.Scanner;
 
public class HW3 {
   public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      System.out.print("난수의 seed값과 심볼 테이블 크기를 입력: ");
      long seed = sc.nextLong();
      int size = sc.nextInt();
      
      LinearProbingHashST<Integer,Integer> lht = new LinearProbingHashST<>(size);
      DoubleHashingST<Integer,Integer> dht = new DoubleHashingST<>(size);
      CuckooHashingST<Integer,Integer> cht = new CuckooHashingST<>(size, 0.45);
      Random rand = new Random(seed);
      
      int lcount = 0, dcount = 0, ccount = 0;
      for (int i = 0; i < size * 0.45; i++) {
         int key = rand.nextInt(), value;
         if (lht.contains(key))
            value = lht.get(key) + 1;
         else value = 1;
         lcount += lht.put(key, value);
         dcount += dht.put(key, value);
         ccount += cht.put(key, value);
      };
      
      System.out.println("Linear Probing: put count = " + lcount);
      lht.print();
      System.out.println("\nDouble Hashing: put count = " + dcount);
      dht.print();
      System.out.println("\nCuckoo Hashing: put count = " + ccount);
      cht.print();
      
      sc.close();
   }
}
 
//여기서 부터 해쉬 테이블 클래스를 정의하는 프로그램 추가할 것!
class LinearProbingHashST<T1,T2>
{
   
   private int M;
   private int pairs;
   private int maxSearchLeng;
   private T1 maxSearchLengKey;
   
   private double avgSearchLeng;
   private int totalSearchLeng;
   private int totalSearchCount;
   private T1[] key_table;
   private T2[] value_table;
   
   @SuppressWarnings("unchecked")
   public LinearProbingHashST(int size)
   {
 
      
      for(int i=size;;i++)
      {
         if(isPrime(i))
         {
            this.M=i;
            break;
         }
         
      
      }
      
      pairs=0;
      totalSearchCount=0;
      key_table=(T1[])new Object[M];
      value_table=(T2[])new Object[M];
      maxSearchLeng=-1;
      
   }
   private int hash(T1 key)
   {
      return (key.hashCode()&0x7fffffff)%M;
   }
   public void print()
   {
      
      
      
      
      System.out.println("테이블의 크기 = "+M);
      System.out.println("저장된 (key, value) 쌍의 수 = "+pairs);
      System.out.println("평균 검색 길이 = "+avgSearchLeng);
      System.out.println("최대 검색 길이= "+maxSearchLeng+" (key = "+maxSearchLengKey+")");
      
   }
    boolean isPrime(int n) {
           if( n<2 ) return false;
           for( int i=2; i<=(int)Math.sqrt(n); i++)
               if( n%i == 0) return false;
           return true;
       }
   
    
    
   public boolean contains(T1 key)
   {int count=1;
      for(int i=hash(key);key_table[i]!=null;i=(i+1)%M,count++)
      {   
         if(key.equals(key_table[i]))
         {
            
            totalSearchCount++;
            if(count>maxSearchLeng)
            {
               maxSearchLeng=count;
               maxSearchLengKey=key;
            }
            totalSearchLeng+=count;
            avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
            return true;
         }
      }
      
      totalSearchCount++;
      if(count>maxSearchLeng)
      {
         maxSearchLeng=count;
         maxSearchLengKey=key;
      }
      totalSearchLeng+=count;
      avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
      return false;
   }
   
   
   
   public T2 get(T1 key)
   {int count=1;
      for(int i=hash(key);key_table[i]!=null;i=(i+1)%M,count++)
      {   
         if(key.equals(key_table[i]))
         {
            
            totalSearchCount++;
            if(count>maxSearchLeng)
            {
               maxSearchLeng=count;
               maxSearchLengKey=key;
            }
            totalSearchLeng+=count;
            avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
            return value_table[i];
         }
      }
      
      totalSearchCount++;
      if(count>maxSearchLeng)
      {
         maxSearchLeng=count;
         maxSearchLengKey=key;
      }
      totalSearchLeng+=count;
      avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
      return null;
   }
   
   private void resize(int size)
   {
       LinearProbingHashST<T1, T2> newHashST = new LinearProbingHashST<T1, T2>(size);
        for (int i = 0; i < M; i++) {
            if (key_table[i] != null) {
               newHashST.put(key_table[i], value_table[i]);
            }
        }
        key_table = newHashST.key_table;
        value_table = newHashST.value_table;
        M    = newHashST.M;
   }
   public int put(T1 key, T2 value)
   {
      int count=1;
   
      int i;
      
      
      if(pairs>=M/2)
      {
         resize(2*M);
      }
      
      for(i=hash(key);key_table[i]!=null;i=(i+1)%M,count++)
      {   
         if(key.equals(key_table[i]))
         {
            value_table[i]=value;
            pairs++;
            totalSearchCount++;
            if(count>maxSearchLeng)
            {
               maxSearchLeng=count;
               maxSearchLengKey=key;
            }
            totalSearchLeng+=count;
            avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
            return count;
         }
      }
      key_table[i]=key;
      value_table[i]=value;
      pairs++;
      totalSearchCount++;
      if(count>maxSearchLeng)
      {
         maxSearchLeng=count;
         maxSearchLengKey=key;
      }
      totalSearchLeng+=count;
      avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
      return count;
      
   }
   
   
}
 
class DoubleHashingST<T1,T2>
{
   private int M,M2;
   private int pairs;
   private int maxSearchLeng;
   private T1 maxSearchLengKey;
   
   private double avgSearchLeng;
   private int totalSearchLeng;
   private int totalSearchCount;
   private T1[] key_table;
   private T2[] value_table;
   
   @SuppressWarnings("unchecked")
   public DoubleHashingST(int size)
   {
 
      
      for(int i=size;;i++)
      {
         if(isPrime(i))
         {
            this.M=i;
            break;
         }
         
      
      }
      
      
      for(int i=M-1;i>0;i--)
      {
         if(isPrime(i))
         {
            this.M2=i;
            break;
         }
         
      
      }
      
      
      pairs=0;
      totalSearchCount=0;
      key_table=(T1[])new Object[M];
      value_table=(T2[])new Object[M];
      maxSearchLeng=-1;
      
   }
   private int hash(T1 key)
   {
      return (key.hashCode()&0x7fffffff)%M;
   }
   private int hash2(T1 key)
   {
      return 1+(key.hashCode()&0x7fffffff)%M2;
   }
   public void print()
   {
      
      
      
      
      System.out.println("테이블의 크기 = "+M);
      System.out.println("저장된 (key, value) 쌍의 수 = "+pairs);
      System.out.println("평균 검색 길이 = "+avgSearchLeng);
      System.out.println("최대 검색 길이 = "+maxSearchLeng+" (key = "+maxSearchLengKey+")");
      
   }
    boolean isPrime(int n) {
           if( n<2 ) return false;
           for( int i=2; i<=(int)Math.sqrt(n); i++)
               if( n%i == 0) return false;
           return true;
       }
   
    
   private void resize(int size)
   {
      DoubleHashingST<T1, T2> newHashST = new DoubleHashingST<T1, T2>(size);
        for (int i = 0; i < M; i++) {
            if (key_table[i] != null) {
               newHashST.put(key_table[i], value_table[i]);
            }
        }
        key_table = newHashST.key_table;
        value_table = newHashST.value_table;
        M    = newHashST.M;
   }
   public int put(T1 key, T2 value)
   {
      int count=1;
   
      
      if(pairs>=M/2)
      {
         resize(2*M);
      }
   
      
 
      int index=hash(key);
      
      if(key_table[index]!=null)
      {
         
         if(key_table[index].equals(key))
         {
            
            value_table[index]=value;
            
            pairs++;
            totalSearchCount++;
            if(count>maxSearchLeng)
            {
               maxSearchLeng=count;
               maxSearchLengKey=key;
            }
            totalSearchLeng+=count;
            avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
            return count;
         }
         
         int i=1;
         while(true)
         {
            int newIndex=((index+i*hash2(key))&0x7fffffff)%M;
            
            count++;
            if(key_table[newIndex]!=null)
            {   
               
               if(key_table[newIndex].equals(key))
            {
               value_table[newIndex]=value;
               pairs++;
               totalSearchCount++;
               if(count>maxSearchLeng)
               {
                  maxSearchLeng=count;
                  maxSearchLengKey=key;
               }
               totalSearchLeng+=count;
               avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
               return count;
            }
            
               
            }
            else
            {
               key_table[newIndex]=key;
               value_table[newIndex]=value;
               pairs++;
               totalSearchCount++;
               if(count>maxSearchLeng)
               {
                  maxSearchLeng=count;
                  maxSearchLengKey=key;
               }
               totalSearchLeng+=count;
               avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
               return count;
            }
            i++;
         }
         
      }
      else
      {
         key_table[index]=key;
         value_table[index]=value;
         pairs++;
         totalSearchCount++;
         if(count>maxSearchLeng)
         {
            maxSearchLeng=count;
            maxSearchLengKey=key;
         }
         totalSearchLeng+=count;
         avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
         return count;
      }
      
      
      
      
   }
}
 
 
 
 
class CuckooHashingST<T1,T2>
{
   private int M,M1,M2;
   private int pairs;
   private int maxSearchLeng;
   private T1 maxSearchLengKey;
   
   private double avgSearchLeng;
   private int totalSearchLeng;
   private int totalSearchCount;
  // private T1[] key_table1,key_table2;
   //private T2[] value_table1,value_table2;
   private T1[] kt1, kt2;
   private T2[] vt1, vt2;
   private double fillFactor;
   private double maxLoop;
   
   @SuppressWarnings("unchecked")
   public CuckooHashingST(final int size, final double fillFactor) {
  //M: size
  //M1: (M / 2 + 1)보다 같거나 큰 수들 중에서 가장 작은 소수
  //M2: M – M1
  for(int i=size;i>1;i++) {
      if(isPrime(i)) {
          this.M=i;
          break;
      }
  }
 
      for(int i=M/2+1;i>1;i++) {
          if(isPrime(i)) {
              this.M1=i;
              break;
          }
      }
      M2=M-M1;
      System.out.println("Cuckoo M: " + M);
      System.out.println("Cuckoo M1: " + M1);
      System.out.println("Cuckoo M2: " + M2);
      
      
      this.fillFactor = fillFactor;
      maxLoop = 3 * ( (Math.log(M*fillFactor) / Math.log(1+0.5+fillFactor)) );
      pairs=0;
      totalSearchCount=0;
      kt1 = (T1[])new Object[M1];
      kt2 = (T1[])new Object[M2];    
      vt1 = (T2[])new Object[M1];    
      vt2 = (T2[])new Object[M2];    
      
      maxSearchLeng = -1;
   }
   private int h1(T1 key) {
       return (key.hashCode()&0x7fffffff) % M1;
   }
   private int h2(T1 key) {
       return (key.hashCode()&0x7fffffff) % M2;
   }
   public void print() {
  for(int i=0;i<M1;i++) {
  if(kt1[i] == null) continue;
  lookup((T1)kt1[i]);
  }for(int i=0;i<M2;i++) {
  if(kt2[i] == null) continue;
  lookup((T1)kt2[i]);
  }
      System.out.println("테이블1의 크기 = "+M1+", 테이블의 크기 = "+M2);
      System.out.println("저장된 (key, value) 쌍의 수 = "+pairs);
      System.out.println("평균 검색 길이 = "+avgSearchLeng);
      System.out.println("최대 검색 길이 = "+maxSearchLeng+" (key = "+maxSearchLengKey+")");   
   }
   boolean isPrime(int n) {
  if(n<2) return false;
   
  for(int i=2; i*i<=n; i++) {
        if(n%i == 0) return false;
  }
  return true;
   }
   
    private int lookup(T1 k) {
    
    System.out.println("lookup함수======");
    System.out.println("Key: " + k);
    System.out.println("h1(key): " + h1(k));
    System.out.println("h2(key): " + h2(k));
    int idx1 = h1(k);
    int idx2 = h2(k);
    int searchLeng = 1;
    if(kt1[idx1] == k) {
             totalSearchCount++;
             searchLeng = 1;
             if(searchLeng>maxSearchLeng)
             {
                maxSearchLeng = searchLeng;
                maxSearchLengKey = k;
             }
             totalSearchLeng += searchLeng;
             avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
             return 1;
        }
    else if(kt2[idx2] == k) {
            totalSearchCount++;
            searchLeng = 2;
            if(searchLeng>maxSearchLeng)
            {
               maxSearchLeng = searchLeng;
               maxSearchLengKey = k;
            }
            totalSearchLeng += searchLeng;
            avgSearchLeng=(double)totalSearchLeng/(double)(totalSearchCount);
    return 2;
        }
 
          return 0;
    }
    
    private void rehash() {        
        CuckooHashingST<T1, T2> newHashST = new CuckooHashingST<T1, T2>((M*2)+1, fillFactor);
 
        
        for (int i = 0; i < M1; i++) {
        if(kt1[i] != null) {
        newHashST.put(kt1[i], vt1[i]);
        }
        }
        for (int i = 0; i < M2; i++) {
        if(kt2[i] != null) {
        newHashST.put(kt2[i], vt2[i]);
        }
        }
 
        System.out.println("Cuckoo nt1.length: " + newHashST.kt1.length);
        System.out.println("Cuckoo nt2.length: " + newHashST.kt2.length);
        kt1 = newHashST.kt1;
        kt2 = newHashST.kt2;
        vt1 = newHashST.vt1;
        vt2 = newHashST.vt2;
        M = newHashST.M;
        M1 = newHashST.M1;
        M2 = newHashST.M2;
        maxLoop = newHashST.maxLoop;
 
        System.out.println("Cuckoo M: " + M);
        System.out.println("Cuckoo M1: " + M1);
        System.out.println("Cuckoo M2: " + M2);
        System.out.println("Cuckoo kt1.length: " + kt1.length);
        System.out.println("Cuckoo kt2.length: " + kt2.length);
        
    }
    
    private void resize() {
    // M = (2 * M + 1)보다 갖거나 큰 수들 중에서 가장 작은 소수
    for(int i=M*2+1;i>0;i++) {
        if(isPrime(i)) {
        M = i;
        break;
        }
    }
 
        for(int i=M/2+1;i>1;i++) {
           if(isPrime(i)) {
              this.M1=i;
              break;
           }
        }
        
        M2=M-M1;
        maxLoop = 3 * ( (Math.log(M*fillFactor) / Math.log(1+0.5-fillFactor)) );
    }
   
    public T2 get(T1 k) {
    int idx1 = h1(k);
    if(kt1[idx1] == k) 
    return vt1[idx1];
    
    int idx2 = h2(k);
    if(kt2[idx2] == k)
    return vt2[idx2];
    
    return null;
    }
    public int put(T1 k, T2 v) {
    
    System.out.println("Cuckoo put=================");
    System.out.println("key: " + k);
int idx1 = h1(k);
    int idx2 = h2(k);
    boolean flag = true;
    T1 old_k = k;
    T2 old_v = v;
    T1 tempk = null;
    T2 tempv = null;
    
    
    for(int i=0; i<maxLoop; i++) {
    idx1 = h1(k);
    if(kt1[idx1] == null) { // 빈집 
    kt1[idx1] = k;
    vt1[idx1] = v;
    pairs++;
    return 1;
    }
    if(kt1[idx1] == k) { //동지 
    vt1[idx1] = v;
    pairs++;
    return 1;
    }
    
    tempk = kt1[idx1];
    tempv = vt1[idx1];
    kt1[idx1] = k;
    vt1[idx1] = v;
    k = tempk;
    v = tempv;
    
    idx2 = h2(k);          // 쫓겨난 
    if(kt2[idx2] == null) { // 빈
    kt2[idx2] = k;
    vt2[idx2] = v;
    pairs++;
    return 1;
    }
    if(kt2[idx2] == k) { // 동
    vt2[idx2] = v;
    pairs++;
    // lookup(k);
    return 1;
    }
 
    tempk = kt2[idx2];
    tempv = vt2[idx2];
    kt2[idx2] = k; 
    vt2[idx2] = v;
    k = tempk;
    v = tempv;
    flag=false;
    }
    
    System.out.println("무언가 많이 잘못 되었다.");
    System.out.println("rehash");
    rehash();
    put(k, v);
 
    return 1; // 점수의 영향 없음 무시.
    }
   
}
