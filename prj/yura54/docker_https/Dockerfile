# ベースイメージとしてUbuntuを使用
FROM ubuntu:22.04

# 対話プロンプトが表示されないように設定
ENV DEBIAN_FRONTEND=noninteractive

# NginxとOpenSSLのインストール
RUN apt-get update && \
    apt-get install -y nginx openssl && \
    apt-get install -y git vim && \
    apt-get install -y curl build-essential && \
    rm -rf /var/lib/apt/lists/*

# Rustのインストール
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"
# GOのインストール

# 証明書を格納するディレクトリを作成
RUN mkdir -p /etc/nginx/ssl

# 自己署名証明書（SSL証明書と秘密鍵）をコンテナ内に自動生成
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/nginx.key \
    -out /etc/nginx/ssl/nginx.crt \
    -subj "/C=JP/ST=Tokyo/L=Chiyoda/O=Example/CN=localhost"

# カスタムのNginx設定ファイルをコンテナにコピー（後述）
COPY default.conf /etc/nginx/conf.d/default.conf

# 80番（HTTP）と443番（HTTPS）ポートを開放
EXPOSE 80 443

# Nginxをフォアグラウンドで起動
CMD ["nginx", "-g", "daemon off;"]
