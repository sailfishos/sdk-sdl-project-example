Name: harbour-sdltest
Summary: Sailfish SDK SDL Example
Version: 0.0.1
Release: 1
Group: Applications
License: LICENSE
URL: http://example.org/
Source0: %{name}-%{version}.tar.bz2
BuildRequires: pkgconfig(sdl2)
BuildRequires: pkgconfig(egl)
BuildRequires: pkgconfig(glesv1_cm)
BuildRequires: pkgconfig(glesv2)
BuildRequires: pkgconfig(SDL2_image)
BuildRequires: pkgconfig(SDL2_ttf)
BuildRequires: pkgconfig(SDL2_mixer)

%{!?qtc_qmake5:%define qtc_qmake5 %{qmake5}}
%{!?qtc_make:%define qtc_make make}

%description
Short description of my SailfishOS Application

%prep
%setup -q -n %{name}-%{version}
# Command used to configure / set up the application
#%configure

%build

%{qtc_qmake5}
%{qtc_make}

%install
rm -rf %{buildroot}
# Command used to install files into %{buildroot}
%make_install

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/86x86/apps/%{name}.png
