# nodeos 시작
```
nodeos -e -p eosio \
--plugin eosio::producer_plugin \
--plugin eosio::chain_api_plugin \
--plugin eosio::http_plugin \
--plugin eosio::history_plugin \
--plugin eosio::history_api_plugin \
--data-dir /home/cafemoca/contracts/eosio/data \
--config-dir /home/cafemoca/contracts/eosio/config \
--access-control-allow-origin='*' \
--contracts-console \
--http-validate-host=false \
--verbose-http-errors \
--filter-on='*' >> nodeos.log 2>&1 &
```
위 설정은 다음 항목들을 완료한다.
* Using a work directory for blockchain data and configuration in eosio directory under the development directory. Here we use eosio/data and eosio/config respectively

* Run the Nodeos. This command loads all the basic plugins, set the server address, enable CORS and add some contract debugging and logging.

* Enable CORS with no restrictions (*)

> 위 configuration에서, CORS는 가능해진다 *를 오직 개발목적으로. 절대로 CORS를 퍼블릭으로 접근가능한 노드에서 *하지 않는게 좋다.


# nodeos의 endpoint
This will check that the RPC API is working correctly, pick one.

1. Check the get_info endpoint provided by the chain_api_plugin in your browser: http://localhost:8888/v1/chain/get_info
2. Check the same thing, but in console on your host machine


# EOS create wallet
* default로 wallet 생성 옵션 --to-console
* production에서 cleos를 사용중이라면, --to-file 옵션을 사용하자. 이렇게 되면 wallet password가 bash_history에 저장되지 않는다. 

개발 목적을 위해 그리고 이것들은 생산 키가 아니라 개발이기 때문에 --to-console은 보안 위협을 제기하지 않는다.
> cleos wallet create --to-console

만약 
# EOS password
> PW5JN51eHeexe8FUxb5NLYW4yqADnzVJHitHLBmf9YgkFWBH39VVQ

## wallet은 토큰을 갖고 있지 않다.
wallet은 암호화된 파일에 private key와 승인된 트랜잭션들을 저장한다.

## wallet과 transaction
보통 인터페이스를 통해 사용자가 transaction object를 build하면 object를 wallet에 보내고 이것은 승인되는데, walletㅇ느 그 후 transaction object를 네트워크에 브로드케스트된 승인과 함께 반환된다. transaction이 유효하다고 네트워크가 확인하면, 블록체인의 블록에 포함된다. 

## wallet의 unlock
> $ cleos wallet list

다음과 같은 명령어는 지갑목록을 반환한다.

```
Wallets:
[
  "default"
]
```

여기서 지갑을 사용하기 위해선 unlock 작업이 필요하다.

> $ cleos wallet unlock

위 명령어를 입력하면 비밀번호를 요구한다. 처음에 cleos create wallet --to-console 명령을 통해 반환되었던 비밀번호를 입력하자.

그리고 다시 cleos wallet list를 입력하면 계정에 asterrisk가 붙은걸 볼 수 있다.

```
Wallets:
[
  "default *"
]
```

**asterrisk**의 의미는 계정이 unlock되었음을 알린다.

# public key 생성

> cleos wallet create_key

나의 private 키: EOS8MxBHZXroce2atNhFbKRUA3z6Zn1WQizUa5MEaTZD5Z2hdt9BB

# import development key
모든 새로운 EOSIO 체인에는 default "system"일고 사용자가 호출한 "eosio"가 있다. 이 계정은 로딩하는 시스템 컨트렉트를 지시한 goverance와 EOSIO 체인의 합의에 의해 체인이 설정하는데 사용된다. 

> $ cleos wallet import

private key를 입력하면 developement key를 발급해준다.
EOS tutorial에서는 임의로 private key를 주는데 이것을 실제 dapp만들땐 공개된 키이므로 사용하지 말아야한다.
>5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3


# account ? ? ?
account는 authorisations를 블록체인에 저장하고 송신자와 수신자를 확인하는데 사용한다. 


# EOSIO type
EOSIO는 몇가지 type들이 typedef 되어있다. 그중에서도 가장 자주 볼 수 있는게 name타입이다.

# contract 
## contract set
> cleos set contract hello /home/CafeM0ca/contracts/hello -p hello@active
## contract execute
> cleos push action hello(실행파일) hi(함수이름) '["bob"]'(인자) -p bob@active(호출자)

## contract를 위한 account
contract를 depoloy하기 위해서는 account가 반드시 필요하니 만들자.
wallet unlock하는거 잊지말것.

여기서는 eosio development key를 depoly하기 위해 사용한다.
> cleos create account eosio eosio.token EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

## contract 배포 정리
1. account 생성
2. 소스코드 작성
3. wasm으로 컴파일
4. depoloy
5. 실행

## action 옵션
* -j : return transaction as json
* -d : don't broadcast 

# ABI file
API는 트랜잭션이 실행될때 전달될 수 있다. 메시지와 액션은 컨트랙트로 넘어가고 ABI에게 확인받을 필요가 없다. ABI는 가이드일뿐 gatekeeper(문지기: 검사하는 정도)가 아니다.

## ABI skeleton file
```
{
   "version": "eosio::abi/1.0",
   "types": [],
   "structs": [],
   "actions": [],
   "tables": [],
   "ricardian_clauses": [],
   "abi_extensions": [],
   "___comment" : ""
}
```
## Types
> EOSIO의 내장 타입들은 ABI file에 묘사될 필요가 없다. 만약 본인이 EOSIO의 내장된것들이 더 친숙하다고 생각하면 정의해도 된다.

## Structs
구조체들은 ABI에 노출되며 묘사되어야한다.   

_eosio.token_ 에서 몇개의 구조체들은 정의가 필요하다. 기억해둘것은 모든 구조체들이 명확하게 정의된게 아니라 몇가지 actions의 매개변수들에 일치하는 것만 해당하는 것이다. 

## Tables
테이블에는 JSON 객체의 정의가 써있다.

account table과 stats table을 보자.
* account table
```
{
  "name": "accounts",
  "type": "account", // Corresponds to previously defined struct
  "index_type": "i64",
  "key_names" : ["primary_key"],
  "key_types" : ["uint64"]
}
```

* stats table
```
{
  "name": "stat",
  "type": "currency_stats",
  "index_type": "i64",
  "key_names" : ["primary_key"],
  "key_types" : ["uint64"]
}
```


두 테이블에서 key_name이 같은 것을 볼 수 있다. 이렇게 구현함으로써 무슨 값이 주어지든 다른 테이블에 쿼리로 삽입할 수 있다. 

# Data Persistence
table의 data 구조체는 수정되어서는 안된다. 테이블의 데이터 구조체를 바꾸고 싶다면 우선 모든 rows를 지워야한다.

* code: contract의 account를 나타낸다. __code_를 통해 접근할 수 있다.
* scope: 컨트랙트의 유일성을 보장한다.  

## source code
```
#include <eosiolib/eosio.hpp>

using namespace eosio;


// 이중대괄호 문법은 컴파일타임에 체크하는 문법
class [[eosio::contract]] addressbook : public eosio::contract {

  public:

        addressbook(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) {

        }

        // update insert = upsert
        [[eosio::action]] void upsert(name user, std::string first_name, std::string last_name, std::string street, std::string city, std::string state){

                require_auth(user);                                                             // user가 호출자랑 같은 지 판단
                address_index addresses(_code, _code.value);
                auto iterator = addresses.find(user.value);
                if(iterator == addresses.end())                                 // user가 table에 없으면 새로 생성
                {
                        addresses.emplace(user, [&](auto& row){
                                row.key = user;
                                row.first_name = first_name;
                                row.last_name = last_name;
                                row.street = last_name;
                                row.street = street;
                                row.city = city;
                                row.state = state;
                        });
                }
                else {                                                                             // user가 table에 있 으면 수정
                        std::string changes;
                        addresses.modify(iterator, user, [&](auto& row){
                                row.key = user;
                                row.first_name = first_name;
                                row.last_name = last_name;
                                row.street = street;
                                row.city = city;
                                row.state = state;
                        });
                }
        }

        [[eosio::action]] void erase(name user){
                // 호출자가 user랑 같은지 확인
                require_auth(user);
                address_index addresses(_code, _code.value);
                auto iterator = addresses.find(user.value);
                eosio_assert(iterator != addresses.end(), "Record does not exist");
                addresses.erase(iterator);
        }
  private:
    struct [[eosio::table]] person {
      name key;
      std::string first_name;
      std::string last_name;
      std::string street;
      std::string city;
      std::string state;

      uint64_t primary_key() const { return key.value;}
    };

    typedef eosio::multi_index<"people"_n, person> address_index;
};


EOSIO_DISPATCH(addressbook, (upsert)(erase))
```

* compile
>eosio-cpp -o addressbook.wasm addressbook.cpp --abigen
* create account for contract 
>cleos create account eosio addressbook EOS8PgcnVADyXDjVXdTe91XK4warLefmFGLWbGufn1Hd2CYGWFB2L EOS8PgcnVADyXDjVXdTe91XK4warLefmFGLWbGufn1Hd2CYGWFB2L -p eosio@active
* depoly
>cleos set contract addressbook /home/CafeM0ca/contracts/addressbook -p addressbook@active
* add table
>cleos push action addressbook upsert '["alice", "alice", "liddell", "123 drink me way", "wonderland", "amsterdam"]' -p alice@active
* alice can't add recodes for another user!
>cleos push action addressbook upsert '["alice", "alice", "liddell", "123 drink me way", "wonderland", "amsterdam"]' -p alice@active
* retrieve alice recode
>cleos get table addressbook addressbook people --lower alice --limit 1
* erase alice from table
> cleos push action addressbook erase '["alice"]' -p alice@active

## action constructor

* A permission_level struct
* The contract to call (initialised using eosio::name type)
* The action (initialised using eosio::name type)
* The data to pass to the action, a tuple of positionals that correlate to the actions being called.


# Custom Dispatchers
