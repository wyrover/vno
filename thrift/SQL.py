# coding: utf-8
from sqlalchemy import Column, ForeignKey, Integer, Numeric, String, text
from sqlalchemy.orm import relationship
from sqlalchemy.ext.declarative import declarative_base


Base = declarative_base()
metadata = Base.metadata


class Account(Base):
    __tablename__ = 'account'

    id = Column(Integer, primary_key=True)
    username = Column(String(20), nullable=False)
    password = Column(String(20), nullable=False)
    comment = Column(String(255))


class AdjLayer(Base):
    __tablename__ = 'adj_layer'

    id = Column(Integer, primary_key=True)
    work_surf_id = Column(ForeignKey(u'work_surf.id', ondelete=u'CASCADE'), index=True)
    coal_id = Column(ForeignKey(u'coal.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    num = Column(Integer)
    h = Column(Numeric(8, 2))
    hp = Column(Numeric(8, 2))
    in_cz = Column(Integer)
    comment = Column(String(255))

    coal = relationship(u'Coal')
    work_surf = relationship(u'WorkSurf')


class Coal(Base):
    __tablename__ = 'coal'

    id = Column(Integer, primary_key=True)
    mine_id = Column(ForeignKey(u'mine.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(20))
    minable = Column(Integer, server_default=text("'1'"))
    thick = Column(Numeric(8, 2))
    hw = Column(Numeric(8, 2))
    qa = Column(Numeric(8, 2))
    qr = Column(Numeric(8, 2))
    fore_qr = Column(Numeric(8, 2))
    fore_qa = Column(Numeric(8, 2))
    rank = Column(Integer)
    quality = Column(Integer)
    pressure = Column(Numeric(10, 2))
    gas_content = Column(Numeric(8, 2))
    f_value = Column(Numeric(8, 2))
    res_abundance = Column(Integer)
    complexity = Column(Integer)
    mine_index = Column(Numeric(8, 2))
    var_coeff = Column(Numeric(8, 2))
    stability = Column(Integer)
    dip_angle = Column(Numeric(8, 2))
    czh = Column(Numeric(8, 2))
    czk = Column(Numeric(8, 2))
    czw = Column(Numeric(8, 2))
    hw_sum = Column(Numeric(8, 2))
    rock = Column(Integer)
    hhh = Column(Numeric(8, 2))
    layer_gap = Column(Numeric(8, 2))
    influence_factor = Column(Numeric(8, 2))
    res_a1 = Column(Numeric(8, 2))
    gas_x1 = Column(Numeric(8, 2))
    res_a2 = Column(Numeric(8, 2))
    gas_x2 = Column(Numeric(8, 2))
    pump_wc = Column(Numeric(8, 2))
    pump_k = Column(Numeric(8, 2))
    pump_k2 = Column(Numeric(8, 2))
    pump_k3 = Column(Numeric(8, 2))
    pump_k4 = Column(Numeric(8, 2))
    pump_k1 = Column(Numeric(8, 2))
    pore_datas = Column(String(500))
    rho = Column(Numeric(8, 2))
    vr = Column(Numeric(8, 2))
    gas_w0 = Column(Numeric(8, 2))
    gas_wc2 = Column(Numeric(8, 2))
    gas_wc3 = Column(Numeric(8, 2))
    gas_eta = Column(Numeric(8, 2))
    q0 = Column(Numeric(8, 2))
    eval_method = Column(Integer)
    q0_alpha = Column(Numeric(8, 2))
    qt_alpha = Column(Numeric(8, 2))
    t_alpha = Column(Numeric(8, 2))
    q_lambda = Column(Numeric(8, 2))
    r_lambda = Column(Numeric(8, 2))
    p0_lambda = Column(Numeric(10, 2))
    p1_lambda = Column(Numeric(10, 2))
    t_lambda = Column(Numeric(8, 2))
    a_lambda = Column(Numeric(8, 2))
    p1_k = Column(Numeric(10, 2))
    p2_k = Column(Numeric(10, 2))
    gas_q = Column(Numeric(8, 2))
    core_height = Column(Numeric(8, 2))
    core_area = Column(Numeric(8, 2))
    gas_viscosity = Column(Numeric(8, 2))
    decay_alpha = Column(Numeric(8, 2))
    permeability_lambda = Column(Numeric(8, 2))
    permeability_k = Column(Numeric(8, 2))
    eval_difficult = Column(Integer)
    comment = Column(String(255))
    relative_layer_gap = Column(Numeric(8, 2))
    is_protectable = Column(Integer)

    mine = relationship(u'Mine')


class Complexity(Base):
    __tablename__ = 'complexity'

    id = Column(Integer, primary_key=True)
    name = Column(String(255))
    details = Column(String(255))
    comment = Column(String(255))


class DesignDrillingSurfTechnology(Base):
    __tablename__ = 'design_drilling_surf_technology'

    id = Column(Integer, primary_key=True)
    design_technology_id = Column(ForeignKey(u'design_technology.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    comment = Column(String(255))
    v_offset = Column(Numeric(8, 2))
    h_offset = Column(Numeric(8, 2))
    dp = Column(Numeric(8, 2))
    gp = Column(Numeric(8, 2))
    leading_dist = Column(Numeric(8, 2))
    gbp = Column(Numeric(8, 2))
    l_stripe = Column(Numeric(8, 2))
    ls = Column(Numeric(8, 2))
    ws = Column(Numeric(8, 2))
    hs = Column(Numeric(8, 2))
    gs = Column(Numeric(8, 2))
    wd = Column(Numeric(8, 2))
    hd = Column(Numeric(8, 2))
    l1 = Column(Numeric(8, 2))
    l2 = Column(Numeric(8, 2))
    w = Column(Numeric(8, 2))
    h = Column(Numeric(8, 2))
    top_side = Column(Numeric(8, 2))
    bottom_side = Column(Numeric(8, 2))
    left_side = Column(Numeric(8, 2))
    right_side = Column(Numeric(8, 2))
    lm = Column(Numeric(8, 2))
    close_length = Column(Numeric(8, 2))

    design_technology = relationship(u'DesignTechnology')


class DesignEvalUnit(Base):
    __tablename__ = 'design_eval_unit'

    id = Column(Integer, primary_key=True)
    design_eval_unit_partition_id = Column(ForeignKey(u'design_eval_unit_partition.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    comment = Column(String(255))
    num = Column(Integer)
    l = Column(Numeric(8, 2))
    t = Column(Integer)
    gap = Column(Numeric(8, 2))

    design_eval_unit_partition = relationship(u'DesignEvalUnitPartition')


class DesignEvalUnitPartition(Base):
    __tablename__ = 'design_eval_unit_partition'

    id = Column(Integer, primary_key=True)
    work_surf_id = Column(ForeignKey(u'work_surf.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    comment = Column(String(255))
    l2 = Column(Numeric(8, 2))
    l1 = Column(Numeric(8, 2))
    w = Column(Numeric(8, 2))
    h = Column(Numeric(8, 2))
    l = Column(Numeric(8, 2))
    r = Column(Numeric(8, 2))
    t = Column(Numeric(8, 2))
    v = Column(Numeric(8, 2))

    work_surf = relationship(u'WorkSurf')


class DesignGoafPore(Base):
    __tablename__ = 'design_goaf_pore'

    id = Column(Integer, primary_key=True)
    design_goaf_technology_id = Column(ForeignKey(u'design_goaf_technology.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    h_offset = Column(Numeric(8, 2))
    v_offset = Column(Numeric(8, 2))
    comment = Column(String(255))

    design_goaf_technology = relationship(u'DesignGoafTechnology')


class DesignGoafTechnology(Base):
    __tablename__ = 'design_goaf_technology'

    id = Column(Integer, primary_key=True)
    design_technology_id = Column(ForeignKey(u'design_technology.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    comment = Column(String(255))
    pore_stubble = Column(Numeric(8, 2))
    dp = Column(Numeric(8, 2))
    gs = Column(Numeric(8, 2))
    ls = Column(Numeric(8, 2))
    ws = Column(Numeric(8, 2))
    hs = Column(Numeric(8, 2))
    gp = Column(Numeric(8, 2))
    pore_num = Column(Integer)
    top_dist = Column(Numeric(8, 2))
    h_offset = Column(String(255))
    y_offset = Column(String(255))
    l1 = Column(Numeric(8, 2))
    l2 = Column(Numeric(8, 2))
    w = Column(Numeric(8, 2))
    h = Column(Numeric(8, 2))
    close_length = Column(Numeric(8, 2))

    design_technology = relationship(u'DesignTechnology')


class DesignPore(Base):
    __tablename__ = 'design_pore'

    id = Column(Integer, primary_key=True)
    design_eval_unit_id = Column(ForeignKey(u'design_eval_unit.id', ondelete=u'CASCADE'), index=True)
    design_site_id = Column(ForeignKey(u'design_site.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    d = Column(Numeric(8, 2))
    x1 = Column(Numeric(8, 2))
    y1 = Column(Numeric(8, 2))
    z1 = Column(Numeric(8, 2))
    x2 = Column(Numeric(8, 2))
    y2 = Column(Numeric(8, 2))
    z2 = Column(Numeric(8, 2))
    length = Column(Numeric(8, 2))
    angle1 = Column(Numeric(8, 2))
    angle2 = Column(Numeric(8, 2))
    comment = Column(String(255))
    t = Column(Integer)

    design_eval_unit = relationship(u'DesignEvalUnit')
    design_site = relationship(u'DesignSite')


class DesignSite(Base):
    __tablename__ = 'design_site'

    id = Column(Integer, primary_key=True)
    design_technology_id = Column(ForeignKey(u'design_technology.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    w = Column(Numeric(8, 2))
    h = Column(Numeric(8, 2))
    x = Column(Numeric(8, 2))
    y = Column(Numeric(8, 2))
    z = Column(Numeric(8, 2))
    comment = Column(String(255))

    design_technology = relationship(u'DesignTechnology')


class DesignTechnology(Base):
    __tablename__ = 'design_technology'

    id = Column(Integer, primary_key=True)
    coal_id = Column(ForeignKey(u'coal.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    region = Column(Integer)
    comment = Column(String(255))

    coal = relationship(u'Coal')


class DesignTunnelControlPoint(Base):
    __tablename__ = 'design_tunnel_control_point'

    id = Column(Integer, primary_key=True)
    design_eval_unit_partition_id = Column(ForeignKey(u'design_eval_unit_partition.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    comment = Column(String(255))
    x = Column(Numeric(8, 2))
    y = Column(Numeric(8, 2))
    z = Column(Numeric(8, 2))

    design_eval_unit_partition = relationship(u'DesignEvalUnitPartition')


class DesignWorkSurfControlPoint(Base):
    __tablename__ = 'design_work_surf_control_point'

    id = Column(Integer, primary_key=True)
    design_eval_unit_partition_id = Column(ForeignKey(u'design_eval_unit_partition.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    comment = Column(String(255))
    x = Column(Numeric(8, 2))
    y = Column(Numeric(8, 2))
    z = Column(Numeric(8, 2))

    design_eval_unit_partition = relationship(u'DesignEvalUnitPartition')


class DesignWorkSurfTechnology(Base):
    __tablename__ = 'design_work_surf_technology'

    id = Column(Integer, primary_key=True)
    design_technology_id = Column(ForeignKey(u'design_technology.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    comment = Column(String(255))
    top_side = Column(Numeric(8, 2))
    bottom_side = Column(Numeric(8, 2))
    right_side = Column(Numeric(8, 2))
    l1 = Column(Numeric(8, 2))
    w = Column(Numeric(8, 2))
    h = Column(Numeric(8, 2))
    l2 = Column(Numeric(8, 2))
    left_side = Column(Numeric(8, 2))
    v_offset = Column(Numeric(8, 2))
    h_offset = Column(Numeric(8, 2))
    p_offset = Column(Numeric(8, 2))
    wd = Column(Numeric(8, 2))
    hd = Column(Numeric(8, 2))
    lm = Column(Numeric(8, 2))
    ws = Column(Numeric(8, 2))
    ls = Column(Numeric(8, 2))
    gs = Column(Numeric(8, 2))
    hs = Column(Numeric(8, 2))
    dp = Column(Numeric(8, 2))
    gp = Column(Numeric(8, 2))
    single_rock_tunnel = Column(Integer)
    d_offset = Column(Numeric(8, 2))
    pore_stubble = Column(Numeric(8, 2))
    pore_angle = Column(Numeric(8, 2))
    pore_type = Column(Integer)
    close_length = Column(Numeric(8, 2), nullable=False)

    design_technology = relationship(u'DesignTechnology')


class DrillingRadiusParam(Base):
    __tablename__ = 'drilling_radius_param'

    id = Column(Integer, primary_key=True)
    coal_id = Column(ForeignKey(u'coal.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    r = Column(Numeric(8, 2))
    l = Column(Numeric(8, 2))
    k1 = Column(Numeric(8, 2))
    rho = Column(Numeric(8, 2))
    q0 = Column(Numeric(8, 2))
    a = Column(Numeric(8, 2))
    t = Column(Numeric(8, 2))
    qm = Column(Numeric(8, 2))
    qsum = Column(Numeric(8, 2))
    eta = Column(Numeric(8, 2))
    r0 = Column(Numeric(8, 2))
    p0 = Column(Numeric(8, 2))
    r1 = Column(Numeric(8, 2))
    p1 = Column(Numeric(8, 2), nullable=False)

    coal = relationship(u'Coal')


class DrillingSurf(Base):
    __tablename__ = 'drilling_surf'

    id = Column(Integer, primary_key=True)
    work_area_id = Column(ForeignKey(u'work_area.id', ondelete=u'CASCADE'), index=True)
    tunnel_id = Column(ForeignKey(u'tunnel.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    qr = Column(Numeric(8, 2))
    qa = Column(Numeric(8, 2))
    fore_qr = Column(Numeric(8, 2))
    fore_qa = Column(Numeric(8, 2))
    q4 = Column(Numeric(8, 2))
    comment = Column(String(255))

    tunnel = relationship(u'Tunnel')
    work_area = relationship(u'WorkArea')


class HighDrillingPore(Base):
    __tablename__ = 'high_drilling_pore'

    id = Column(Integer, primary_key=True)
    high_drilling_pore_param_id = Column(ForeignKey(u'high_drilling_pore_param.id', ondelete=u'CASCADE'), index=True)
    num = Column(Integer)
    length = Column(Numeric(8, 2))
    angle = Column(Numeric(8, 2))
    pore_type = Column(Integer)
    comment = Column(String(255))

    high_drilling_pore_param = relationship(u'HighDrillingPoreParam')


class HighDrillingPoreParam(Base):
    __tablename__ = 'high_drilling_pore_param'

    id = Column(Integer, primary_key=True)
    work_surf_id = Column(ForeignKey(u'work_surf.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    lk = Column(Numeric(8, 2))
    lc = Column(Numeric(8, 2))
    lw = Column(Numeric(8, 2))
    n1 = Column(Integer)
    n2 = Column(Integer)
    beta = Column(Numeric(8, 2))
    ld = Column(Numeric(8, 2))
    comment = Column(String(255))

    work_surf = relationship(u'WorkSurf')


class HighDrillingSiteParam(Base):
    __tablename__ = 'high_drilling_site_param'

    id = Column(Integer, primary_key=True)
    work_surf_id = Column(ForeignKey(u'work_surf.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    l1 = Column(Numeric(8, 2))
    l2 = Column(Numeric(8, 2))
    lg = Column(Numeric(8, 2))
    hn = Column(Numeric(8, 2))
    theta = Column(Numeric(8, 2))
    q = Column(Numeric(8, 2))
    rtn = Column(Numeric(8, 2))
    hs = Column(Numeric(8, 2))
    comment = Column(String(255))

    work_surf = relationship(u'WorkSurf')


class HighDrillingTunnel(Base):
    __tablename__ = 'high_drilling_tunnel'

    id = Column(Integer, primary_key=True)
    work_surf_id = Column(ForeignKey(u'work_surf.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    k = Column(Numeric(8, 2))
    rock = Column(Integer)
    hz_min = Column(Numeric(8, 2))
    hz_max = Column(Numeric(8, 2))
    comment = Column(String(255))

    work_surf = relationship(u'WorkSurf')


class HydrGeo(Base):
    __tablename__ = 'hydr_geo'

    id = Column(Integer, primary_key=True)
    name = Column(String(20))
    x1 = Column(Integer)
    x2 = Column(Integer)
    x3 = Column(Integer)
    x4 = Column(Numeric(8, 2))
    x5 = Column(Numeric(8, 2))
    x6 = Column(Numeric(8, 2))
    x7 = Column(Numeric(8, 2))
    x8 = Column(String(255))


class Mine(Base):
    __tablename__ = 'mine'

    id = Column(Integer, primary_key=True)
    tech_mode_id = Column(ForeignKey(u'tech_mode.id', ondelete=u'CASCADE'), index=True)
    mine_region_id = Column(ForeignKey(u'mine_region.id', ondelete=u'CASCADE'), index=True)
    account_id = Column(ForeignKey(u'account.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    province = Column(String(20))
    city = Column(String(20))
    capacity = Column(Numeric(8, 2))
    topo_geo = Column(Integer)
    hydr_geo = Column(Integer)
    ground_condition = Column(Integer)
    qr = Column(Numeric(8, 2))
    qa = Column(Numeric(8, 2))
    fore_qr = Column(Numeric(8, 2))
    fore_qa = Column(Numeric(8, 2))
    gas_k1 = Column(Numeric(8, 2))
    gas_k2 = Column(Numeric(8, 2))
    stereo_schem_diagram = Column(String(255))
    rock_gas_k2 = Column(Numeric(8, 2))
    reserve_w1 = Column(Numeric(8, 2))
    reserve_w2 = Column(Numeric(8, 2))
    reserve_w3 = Column(Numeric(8, 2))
    gas_w0 = Column(Numeric(8, 2))
    gas_wc2 = Column(Numeric(8, 2))
    pump_k2 = Column(Numeric(8, 2))
    pump_k3 = Column(Numeric(8, 2))
    pump_k4 = Column(Numeric(8, 2))
    pump_k1 = Column(Numeric(8, 2))
    pump_k = Column(Numeric(8, 2))
    pump_wc = Column(Numeric(8, 2))
    reserve_gas = Column(Numeric(8, 2))
    comment = Column(String(255))
    protect_layer_condition = Column(Integer)

    account = relationship(u'Account')
    mine_region = relationship(u'MineRegion')
    tech_mode = relationship(u'TechMode')


class MineBase(Base):
    __tablename__ = 'mine_base'

    id = Column(Integer, primary_key=True)
    name = Column(String(50))
    comment = Column(String(255))


class MineRegion(Base):
    __tablename__ = 'mine_region'

    id = Column(Integer, primary_key=True)
    mine_base_id = Column(ForeignKey(u'mine_base.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(20))
    comment = Column(String(255))

    mine_base = relationship(u'MineBase')


class PoreFlow(Base):
    __tablename__ = 'pore_flow'

    id = Column(Integer, primary_key=True)
    name = Column(String(255))
    t = Column(Numeric(8, 2))
    a0 = Column(Numeric(8, 2))
    d = Column(Numeric(8, 2))
    d1 = Column(Numeric(8, 2))
    m = Column(Numeric(8, 2))
    k = Column(Numeric(8, 2))
    delta_t = Column(Numeric(8, 2))
    x = Column(Numeric(8, 2))
    p_test = Column(Numeric(8, 2))
    p_cur = Column(Numeric(8, 2))
    b = Column(Numeric(8, 2))
    pt = Column(Numeric(8, 2))
    delta_p = Column(Numeric(8, 2))
    dh = Column(Numeric(8, 2))
    q_hun = Column(Numeric(8, 2))
    q_chun = Column(Numeric(8, 2))


class PoreSize(Base):
    __tablename__ = 'pore_size'

    id = Column(Integer, primary_key=True)
    name = Column(String(255))
    q = Column(Numeric(8, 2))
    v = Column(Numeric(8, 2))
    d = Column(Numeric(8, 2))
    p = Column(Numeric(8, 2))
    sigma = Column(Numeric(8, 2))
    delta = Column(Numeric(8, 2))
    comment = Column(String(255))


class ResAbundance(Base):
    __tablename__ = 'res_abundance'

    id = Column(Integer, primary_key=True)
    name = Column(String(20))
    min_abundance = Column(Numeric(8, 2))
    max_abundance = Column(Numeric(8, 2))


class Rock(Base):
    __tablename__ = 'rock'

    id = Column(Integer, primary_key=True)
    name = Column(String(50))
    a = Column(Numeric(3, 1))
    b = Column(Numeric(3, 1))
    c = Column(Numeric(3, 1))
    comment = Column(String(255))


class SysInfo(Base):
    __tablename__ = 'sys_info'

    id = Column(Integer, primary_key=True)
    account_id = Column(ForeignKey(u'account.id', ondelete=u'CASCADE'), index=True)
    last_login_time = Column(String(255))
    comment = Column(String(255))

    account = relationship(u'Account')


class TechMode(Base):
    __tablename__ = 'tech_mode'

    id = Column(Integer, primary_key=True)
    mine_region_id = Column(ForeignKey(u'mine_region.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    mode_type = Column(Integer)
    c1 = Column(Integer)
    c2 = Column(Integer)
    c3 = Column(Integer)
    comment = Column(String(255))

    mine_region = relationship(u'MineRegion')


class Technology(Base):
    __tablename__ = 'technology'

    id = Column(Integer, primary_key=True)
    mine_region_id = Column(ForeignKey(u'mine_region.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    iskey = Column(Integer)
    doc = Column(String(255))
    video = Column(String(255))
    comment = Column(String(255))

    mine_region = relationship(u'MineRegion')


class TopoGeo(Base):
    __tablename__ = 'topo_geo'

    id = Column(Integer, primary_key=True)
    name = Column(String(20))
    feature = Column(String(255))
    comment = Column(String(255))


class Tunnel(Base):
    __tablename__ = 'tunnel'

    id = Column(Integer, primary_key=True)
    name = Column(String(255))
    b = Column(Numeric(8, 2))
    h = Column(Numeric(8, 2))
    l = Column(Numeric(8, 2))
    s = Column(Numeric(8, 2))
    d = Column(Numeric(8, 2))
    wh = Column(Numeric(8, 2))
    v = Column(Numeric(8, 2))
    q3 = Column(Numeric(8, 2))
    q0 = Column(Numeric(8, 2))
    comment = Column(String(255))
    tunnel_type = Column(Integer)
    top_side = Column(Numeric(8, 2))
    bottom_side = Column(Numeric(8, 2))
    left_side = Column(Numeric(8, 2))
    right_side = Column(Numeric(8, 2))
    x1 = Column(Numeric(8, 2))
    y1 = Column(Numeric(8, 2))
    z1 = Column(Numeric(8, 2))
    x2 = Column(Numeric(8, 2))
    y2 = Column(Numeric(8, 2))
    z2 = Column(Numeric(8, 2))


class WorkArea(Base):
    __tablename__ = 'work_area'

    id = Column(Integer, primary_key=True)
    coal_id = Column(ForeignKey(u'coal.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    mode = Column(Integer, server_default=text("'1'"))
    a = Column(Numeric(8, 2))
    qr = Column(Numeric(8, 2))
    qa = Column(Numeric(8, 2))
    fore_qr = Column(Numeric(8, 2))
    fore_qa = Column(Numeric(8, 2))
    comment = Column(String(255))

    coal = relationship(u'Coal')


class WorkSurf(Base):
    __tablename__ = 'work_surf'

    id = Column(Integer, primary_key=True)
    work_area_id = Column(ForeignKey(u'work_area.id', ondelete=u'CASCADE'), index=True)
    tunnel_id = Column(ForeignKey(u'tunnel.id', ondelete=u'CASCADE'), index=True)
    name = Column(String(255))
    a = Column(Numeric(8, 2))
    qr = Column(Numeric(8, 2))
    qa = Column(Numeric(8, 2))
    fore_qr = Column(Numeric(8, 2))
    fore_qa = Column(Numeric(8, 2))
    l1 = Column(Numeric(8, 2))
    l2 = Column(Numeric(8, 2))
    layerable = Column(Integer)
    k1 = Column(Numeric(8, 2))
    k2 = Column(Numeric(8, 2))
    k3 = Column(Numeric(8, 2))
    kf = Column(Numeric(8, 2))
    method = Column(Integer)
    last_t = Column(Numeric(8, 2))
    qr1 = Column(Numeric(8, 2))
    qr2 = Column(Numeric(8, 2))
    comment = Column(String(255))

    tunnel = relationship(u'Tunnel')
    work_area = relationship(u'WorkArea')
