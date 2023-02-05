acc = 0
acclist = []
optimizer = torch.optim.SGD(model.parameters(), lr=0.01, momentum=0.8, weight_decay=1e-4)
lr_schedular = torch.optim.lr_scheduler.StepLR(optimizer=optimizer, step_size=50, gamma=0.5)

for epoch in range(200):
    pb = tqdm(total=sample_size, ncols=100)
    
    for step, (x, y) in enumerate(train_dl):
        l = train_step(x, y)      
        pb.set_postfix({"Loss": l.detach().cpu().numpy()})
        pb.update(x.size()[0])
    
    cor, tot = 0, 0
    for step, (x, y) in enumerate(valid_dl):
        step_c, step_t = test_step(x, y)
        cor += step_c
        tot += step_t
        pb.update(x.size()[0])
    
    acc = cor / tot
    acclist.append(acc)
    pb.close()

    print(f"epoch: {epoch}\tacc: {acc}\ttotal: {tot}\tLR: {optimizer.state_dict()['param_groups'][0]['lr']}") 
    lr_schedular.step() 
    state = {
        'model': model.state_dict(),
        'optimizer': optimizer.state_dict()
    }
    torch.save(state, "models/demo.pth")

model = Model().to(device)
model.load_state_dict(torch.load("models/demo.pth").get('model'))

