# [Windows] codespacesでの実行方法
1. （初回のみ）コマンドプロンプトで以下を実行して、VcXsrvをインストール
    ```shell
    winget install -e --id marha.VcXsrv
    ```

1. （初回のみ）コマンドプロンプトで以下を実行して、GitHub Cliをインストール
    ```shell
    winget install -e --id GitHub.cli
    ```

1. （初回のみ）コマンドプロンプトを一旦閉じて、再度開く
   
1. ブラウザでcodespacesを実行
   
1. VcXsrvを実行（ショートカットXLaunchをダブルクリック）
    
1. （初回のみ）コマンドプロンプトでgithubにログイン
    ```shell
    gh auth login -s codespace
    ```
   - （初回のみ）表示された質問に以下で回答
    ```shell
    ? What account do you want to log into?  [Use arrows to move, type to filter]
    > GitHub.com
      GitHub Enterprise Server
    ```
    ```shell
    ? What is your preferred protocol for Git operations?  [Use arrows to move, type to filter]
    > HTTPS
      SSH
    ```
    ```shell
    ? Authenticate Git with your GitHub credentials? (Y/n) Y
    ```
    ```shell
    ? How would you like to authenticate GitHub CLI?  [Use arrows to move, type to filter]
    > Login with a web browser
      Paste an authentication token
    ```
    - ブラウザが開くので認証を行う
    ```
    ! First copy your one-time code: XXXX-XXXX
    ``` 
    - ブラウザ認証時にMachine Codeの入力画面が表示されたら、コマンドプロンプトに表示されたコード（上記の XXXX-XXXX）を入力

1. コマンドプロンプトでcodespacesにssh接続
    ```shell
    set DISPLAY=localhost:0.0
    gh cs ssh -- -XY
    ```
    - 表示されたcodespaceを選択する
    ```shell
    ? Choose codespace:  [Use arrows to move, type to filter]
    > [リポジトリ名] (main): [codespace名]
    ```
1. ssh接続しているコマンドプロンプトで、ビルド（makeやc++など）して実行
   