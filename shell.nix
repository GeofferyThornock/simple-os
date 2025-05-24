let
  nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/release-23.11";
  pkgs = import nixpkgs { crossSystem = { config = "i686-elf"; }; };
in

# callPackage is needed due to https://github.com/NixOS/nixpkgs/pull/126844
pkgs.pkgsStatic.callPackage ({ mkShell, grub2, libgcc, xorriso, newlib, gcc, binutils }: mkShell {
  # these tools run on the build platform, but are configured to target the host platform
  nativeBuildInputs = [ gcc binutils grub2 libgcc xorriso  ];
  # libraries needed for the host platform
  buildInputs = [ newlib ];
}) {}
