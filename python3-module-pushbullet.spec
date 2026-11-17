Name: python3-module-pushbullet
Version: 0.12.0
Release: alt1

Summary: A simple Python client for pushbullet.com
License: MIT
Group: Development/Python3
Url: https://github.com/randomchars/pushbullet.py

BuildArch: noarch
Source: %name-%version.tar

BuildRequires(pre): rpm-build-python3
BuildRequires: python3-module-setuptools python3-module-wheel rpm-build-pyproject

%description
This is a Python library for the Pushbullet service. It allows you to send push notifications to Android and iOS devices.

%prep
%setup

%build
%pyproject_build

%install
%pyproject_install

%files
%python3_sitelibdir/pushbullet/
%python3_sitelibdir/*dist-info/

# %python3_sitelibdir/pushbullet.py-*.egg-info/
# This was the older version , which was going to expire so replaced with  /*dist-info/ ---- line number 30