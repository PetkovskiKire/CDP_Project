var app = new Vue({
    el: '#vueapp',
    data: {
        userid: "",
        password: "",
        applications: [],
        cpuload: 0,
        description: "",
        systemUseNotification: "",
        errorMessage: "",
        name: "",
        timeelapsed: 0,
        components: []
    },
    methods: {
        submit: function (message) {
            $('.ui.modal').modal('hide');
        }
    }
});

class NotificationListener {
    applicationAcceptanceRequested(request) {
        app.systemUseNotification = request.systemUseNotification();
        return new Promise(function(resolve, reject) {
            if (request.systemUseNotification()) {
                $('.ui.mini.modal')
                  .modal({
                     closable  : false,
                     onApprove : function() {
                         resolve();
                     },
                     onHide : function() {
                         resolve();
                     }
                  })
                  .modal('show')
                ;
            }
            else
                resolve();
        });
    }

    credentialsRequested(request) {
        if (request.userAuthResult().code() == studio.api.INVALID_CHALLENGE_RESPONSE)
            app.errorMessage = request.userAuthResult().text();
        else
            app.errorMessage = '';
        app.userid = '';
        app.password = '';
        return new Promise(function(resolve, reject) {
            $('.ui.tiny.modal')
                .modal({
                    keyboardShortcuts: true,
                    closable  : false,
                    onDeny    : function(){
                        reject();
                        return false;
                    },
                    onApprove : function() {
                        resolve({Username: app.userid, Password: app.password});
                    },
                    onHide : function() {
                        resolve({Username: app.userid, Password: app.password});
                    }
                })
                .modal('show')
            ;
        });
    }
}

var client = new studio.api.Client(window.location.host, new NotificationListener());

var componentHandler = function (child) {
    if (child.info().node_type == studio.protocol.CDPNodeType.CDP_COMPONENT || child.info().node_type == studio.protocol.CDPNodeType.CDP_OPERATOR) {
        var componentModel = {
            name: child.name(),
            description: "",
            fs: 0,
            priority: "",
            state: "",
            suspended: false,
            timer: 0,
            period: 0,
            components: []
        }
        app.components.splice(-1, 0, componentModel)

        child.subscribeToChildValues("Description", function (value) {
            componentModel.description = value;
        });
        child.subscribeToChildValues("fs", function (value) {
            componentModel.fs = value;
        });
        child.subscribeToChildValues("CurrentState", function (value) {
            componentModel.state = value;
        });
        child.subscribeToChildValues("Priority", function (value) {
            componentModel.priority = value;
        });
        child.subscribeToChildValues("Suspended", function (value) {
            componentModel.suspended = value;
        });
        child.subscribeToChildValues("Process Timer", function (value) {
            componentModel.timer = value;
        });
        child.subscribeToChildValues("Process Period", function (value) {
            componentModel.period = value;
        });
    }
};

client.root().then(function (system) {
    system.forEachChild(function(cdpapp) {
        if (cdpapp.info().is_local) {
            cdpapp.subscribeToChildValues("CPULoad", function (value) {
                app.cpuload = value * 100;
            });
            cdpapp.subscribeToChildValues("Description", function (value) {
                app.description = value;
            });
            cdpapp.subscribeToChildValues("Name", function (value) {
                app.name = value;
            });

            cdpapp.subscribeToStructure(function (name, action){
                if (action == studio.api.structure.ADD) {
                    cdpapp.child(name).then(componentHandler);
                } else {
                    app.components = app.components.filter(function(component, index) {
                        return component.name!=name;
                    });
                }

            });
        }
    });
});

