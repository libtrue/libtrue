# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
  config.vm.guest = :freebsd
  config.vm.synced_folder ".", "/vagrant", id: "vagrant-root", disabled: true

  config.vm.box = "freebsd/FreeBSD-11.0-RELEASE-p1"

  config.ssh.shell = "sh"
  config.vm.network :forwarded_port, guest: 9000, host: 9000

  config.vm.base_mac = "080027FA8C33"

  config.vm.provider :vmware_fusion do |v|
    v.vmx["memsize"] = "1024"
    v.vmx["numvcpus"] = "1"
  end

  config.vm.provider :virtualbox do |vb|
    vb.customize ["modifyvm", :id, "--memory", "1024"]
    vb.customize ["modifyvm", :id, "--cpus", "1"]
    vb.customize ["modifyvm", :id, "--hwvirtex", "on"]
    vb.customize ["modifyvm", :id, "--audio", "none"]
    vb.customize ["modifyvm", :id, "--nictype1", "virtio"]
    vb.customize ["modifyvm", :id, "--nictype2", "virtio"]
  end

  config.vm.provider :bhyve do |vm|
    vm.disks = [{name: "trytond", size: "2G", format:"raw",}]
    vm.memory = "1024M"
    vm.cpus = "1"
  end

  config.vm.boot_timeout = 3600

  config.vm.provision "ansible" do |ansible|
    ansible.sudo = true
    ansible.extra_vars = { ansible_python_interpreter: '/usr/local/bin/python2.7', ansible_ssh_user: 'vagrant' }
    ansible.raw_arguments = ["--connection=paramiko"]
    ansible.playbook = "playbook.yml"
    ansible.verbose = "v"
  end

end
