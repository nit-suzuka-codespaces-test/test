# [Mac] codespacesでの実行方法
1. （初回のみ）ターミナルで以下を実行して、XQuartzをインストール
    ```shell
    brew install --cask xquartz
    ```
1. XQuartzの環境設定 > セキュリティ > ネットワーク・クライアントからの接続を許可

1. XQuartzを再起動（もしくは Mac再起動）

1. （初回のみ）ターミナルで以下を実行して、GitHub Cliをインストール
    ```shell
    brew install gh
    ```
   
1. ブラウザでcodespacesを実行
    
1. （初回のみ）ターミナルでgithubにログイン
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
    - ブラウザ認証時にMachine Codeの入力画面が表示されたら、ターミナルに表示されたコード（上記の XXXX-XXXX）を入力

1. ターミナルでcodespacesにssh接続
    ```shell
    xhost +localhost
    gh cs ssh -- -XY
    ```
    - 表示されたcodespaceを選択する
    ```shell
    ? Choose codespace:  [Use arrows to move, type to filter]
    > [リポジトリ名] (main): [codespace名]
    ```

1. ssh接続しているターミナルで、ビルド（makeやc++など）して実行
   