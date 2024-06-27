{ pkgs }: {
  deps = [
    pkgs.gcc
    pkgs.pkg-config
    pkgs.gtk3
    pkgs.cairo
    pkgs.glib
    pkgs.glibc
    pkgs.mysql
    pkgs.mysql-client
  ];
}
