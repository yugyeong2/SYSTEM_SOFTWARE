## 암호 찾기

주어진 binarypasswd.exe 프로그램의 암호를 알아내시오.

- 제공된 프로그램은 암호를 입력 받는다. 성공 시 아래와 같은 메세지를 보여주는데, 성
공시의 스크린 샷과 리포트를 작성한다.
- 제공된 프로그램은 윈도우 10, 64bit, Dev-Cpp 5.9.2 TDM-GCC 4.8.1 Setup.exe 이용하여
빌드 되었다.
- 주의 사항
Dev-Cpp 에 포함된 gdb 또는 관련 디버깅 프로그램들을 잘 사용한다.

---

### 정답

**qlalfqjsgh** (비밀번호)

각 ab, cd, ef, gh 함수에서 0 또는 1을 return 하는데,
0이면, 입력받은 값과 해당 부분의 비밀번호가 다르기 때문에 “Wrong Answer”를 출력하고,
1이면, 입력받은 값과 해당 부분의 비밀번호가 같기 때문에 “Correct Password\nCapture
this screen and write report.”를 출력하는 로직의 프로그램이다.

함수 ab, cd, ef, gh에서 비교하는 부분(cmp, strcmp)를 주의 깊게 살펴보면서, breakpoint
를 찍고 레지스터의 값들을 출력해보며 코드를 이해하고 정답을 알아낼 수 있었다.
